#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <atomic>

// logging
std::mutex log_mutex;
void server_log(const std::string &msg) {
    std::lock_guard<std::mutex> lg(log_mutex);
    std::cout << msg << std::endl;
}

const int DEFAULT_PORT = 8080;
// default inactivity timeout in minutes
const int DEFAULT_TIMEOUT_MINUTES = 2;

std::map<int, std::string> clients; // sock -> username
std::map<int, std::chrono::steady_clock::time_point> last_activity;
std::mutex clients_mutex;
std::atomic<bool> running(true);

void safe_send(int sock, const std::string &msg) {
    if (sock <= 0) return;
    ssize_t sent = send(sock, msg.c_str(), msg.size(), 0);
    (void)sent;
}

void broadcast(const std::string &msg, int except_sock = -1) {
    std::lock_guard<std::mutex> lock(clients_mutex);
    for (auto &p : clients) {
        int s = p.first;
        if (s == except_sock) continue;
        safe_send(s, msg);
        // log per-recipient send
        server_log(std::string("[SENT] to ") + p.second + " (sock " + std::to_string(s) + ") : " + msg);
    }
}

int find_sock_by_username(const std::string &username) {
    std::lock_guard<std::mutex> lock(clients_mutex);
    for (auto &p : clients) {
        if (p.second == username) return p.first;
    }
    return -1;
}

void remove_client(int sock) {
    std::string name;
    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        auto it = clients.find(sock);
        if (it != clients.end()) {
            name = it->second;
            clients.erase(it);
            last_activity.erase(sock);
        }
    }
    if (!name.empty()) {
        std::string notice = "[server] " + name + " disconnected\n";
        // broadcast without holding the clients_mutex to avoid deadlock
        broadcast(notice, -1);
        // server-side alert for admin/operator
        std::cout << "[server] ALERT: " << name << " disconnected (socket " << sock << ")" << std::endl;
    }
    shutdown(sock, SHUT_RDWR);
    close(sock);
}

void handle_client(int client_sock) {
    char buffer[1024];
    // 1) Expect username as the first message
    ssize_t len = recv(client_sock, buffer, sizeof(buffer)-1, 0);
    if (len <= 0) {
        close(client_sock);
        return;
    }
    buffer[len] = '\0';
    std::string username(buffer);
    // trim possible newline
    if (!username.empty() && username.back() == '\n') username.pop_back();

    // allow the client to retry usernames until a unique one is chosen
    while (true) {
        bool duplicate = false;
        {
            std::lock_guard<std::mutex> lock(clients_mutex);
            for (auto &p : clients) {
                if (p.second == username) { duplicate = true; break; }
            }
        }
        if (!duplicate) break;

        // inform client the username is taken and ask for a new one
        safe_send(client_sock, std::string("[server] USERNAME_TAKEN\n"));
        server_log(std::string("[REJECT] connection attempt with duplicate username: ") 
              + username + " (sock " + std::to_string(client_sock) + ")");

        // wait for the client to send a different username
        ssize_t r = recv(client_sock, buffer, sizeof(buffer)-1, 0);
        if (r <= 0) { shutdown(client_sock, SHUT_RDWR); close(client_sock); return; }
        buffer[r] = '\0';
        username = std::string(buffer);
        if (!username.empty() && username.back() == '\n') username.pop_back();
    }
    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        clients[client_sock] = username;
        last_activity[client_sock] = std::chrono::steady_clock::now();
    }
    std::string join_msg = "[server] " + username + " joined\n";
    broadcast(join_msg, client_sock);
    safe_send(client_sock, "[server] Welcome, " + username + "\n" + "Available commands:\n" 
        + " - /list : list connected users\n - /quit : disconnect\n - @username message :"
        + "send direct message to username\n  Type your message and hit Enter to broadcast to all users.\n\n");
    // server-side alert for admin/operator
    std::cout << "[server] ALERT: " << username << " joined (socket " << client_sock << ")" << std::endl;
    // log join event
    server_log(std::string("[JOIN] ") + username + " (sock " + std::to_string(client_sock) + ")");

    while (running) {
        len = recv(client_sock, buffer, sizeof(buffer)-1, 0);
        if (len <= 0) break; // disconnect or error
    buffer[len] = '\0';
    std::string msg(buffer);
    // log receive
    server_log(std::string("[RX] from ") + username + " (sock " + std::to_string(client_sock) + ") : " + msg);
        // trim newline at end
        while (!msg.empty() && (msg.back() == '\n' || msg.back() == '\r')) msg.pop_back();

        // update activity
        {
            std::lock_guard<std::mutex> lock(clients_mutex);
            last_activity[client_sock] = std::chrono::steady_clock::now();
        }

        if (msg == "/quit" || msg == "/close") {
            safe_send(client_sock, "[server] Goodbye\n");
            break;
        }

        if (msg == "/list") {
            std::ostringstream oss;
            oss << "[server] Connected users:\n";
            std::lock_guard<std::mutex> lock(clients_mutex);
            for (auto &p : clients) {
                oss << " - " << p.second << "\n";
            }
            safe_send(client_sock, oss.str());
            continue;
        }

        // direct/multicast syntax: one or more @username tokens (or comma-separated) followed by message
        if (!msg.empty() && msg[0] == '@') {
            // parse targets (support @alice @bob msg or @alice,bob msg)
            std::vector<std::string> targets;
            size_t pos = 0;
            while (pos < msg.size() && msg[pos] == '@') {
                size_t space_pos = msg.find(' ', pos);
                std::string token;
                if (space_pos != std::string::npos) {
                    token = msg.substr(pos+1, space_pos - (pos+1));
                    pos = space_pos + 1;
                } else {
                    token = msg.substr(pos+1);
                    pos = msg.size();
                }
                // split token by commas
                size_t start = 0;
                while (start < token.size()) {
                    size_t comma = token.find(',', start);
                    std::string name = (comma == std::string::npos) ? token.substr(start) : token.substr(start, comma - start);
                    if (!name.empty()) targets.push_back(name);
                    if (comma == std::string::npos) break;
                    start = comma + 1;
                }
                // skip any spaces
                while (pos < msg.size() && msg[pos] == ' ') pos++;
                // if next char isn't '@' then we've consumed the target list
                if (pos >= msg.size() || msg[pos] != '@') break;
            }

            // remaining is body
            std::string body;
            if (pos < msg.size()) body = msg.substr(pos);
            // trim leading spaces
            while (!body.empty() && body.front() == ' ') body.erase(body.begin());

            std::string sender;
            {
                std::lock_guard<std::mutex> lock(clients_mutex);
                sender = clients[client_sock];
            }

            if (targets.empty()) {
                safe_send(client_sock, "[server] Invalid direct message format. Use @username message\n");
                continue;
            }


            // deduplicate targets
            std::sort(targets.begin(), targets.end());
            targets.erase(std::unique(targets.begin(), targets.end()), targets.end());

            // deliver to each target, collect missing targets
            std::vector<std::string> missing;
            std::vector<std::string> delivered;
            for (auto &t : targets) {
                int tsock = find_sock_by_username(t);
                if (tsock == -1) {
                    missing.push_back(t);
                } else {
                    safe_send(tsock, std::string("[dm] ") + sender + ": " + body + "\n");
                    delivered.push_back(t);
                    server_log(std::string("[MCAST] from ") + sender + " (sock " + std::to_string(client_sock) + ") to " + t + " (sock " + std::to_string(tsock) + ") : " + body);
                }
            }

            // acknowledge to sender
            if (!delivered.empty()) {
                std::ostringstream ack;
                ack << "[dm->";
                for (size_t i = 0; i < delivered.size(); ++i) {
                    if (i) ack << ",";
                    ack << delivered[i];
                }
                ack << "] " << body << "\n";
                safe_send(client_sock, ack.str());
            }
            if (!missing.empty()) {
                std::ostringstream miss;
                miss << "[server] user(s) not found:";
                for (auto &m : missing) miss << ' ' << m;
                miss << "\n";
                safe_send(client_sock, miss.str());
            }

            continue;
        }

        // broadcast otherwise
        std::string sender;
        {
            std::lock_guard<std::mutex> lock(clients_mutex);
            sender = clients[client_sock];
        }
    std::string out = sender + ": " + msg + "\n";
    // log broadcast intent
    server_log(std::string("[BCAST] from ") + sender + " (sock " + std::to_string(client_sock) + ") : " + msg);
    broadcast(out, client_sock);
    }

    remove_client(client_sock);
}

void server_input_thread(int server_sock) {
    std::string line;
    while (running && std::getline(std::cin, line)) {
        if (line.empty()) continue;
        if (line == "/quit") {
            running = false;
            // close the listening socket so accept() in main unblocks
            // server_sock is the listening fd passed in; close it here
            shutdown(server_sock, SHUT_RDWR);
            close(server_sock);
            break;
        }
        if (line == "/list") {
            std::lock_guard<std::mutex> lock(clients_mutex);
            std::cout << "Connected users:\n";
            for (auto &p : clients) std::cout << " - " << p.second << "\n";
            continue;
        }
        // close a user's connection: /close username
        if (line.rfind("/close ", 0) == 0) {
            std::string u = line.substr(7);
            int s = find_sock_by_username(u);
            if (s != -1) {
                safe_send(s, "[server] You have been disconnected by server\n");
                remove_client(s);
                std::cout << "Closed connection for " << u << "\n";
            } else {
                std::cout << "User not found: " << u << "\n";
            }
            continue;
        }

        // send to user: @username message
        if (line[0] == '@') {
            auto sp = line.find(' ');
            if (sp != std::string::npos) {
                std::string target = line.substr(1, sp-1);
                std::string body = line.substr(sp+1);
                int s = find_sock_by_username(target);
                if (s != -1) {
                    safe_send(s, "[server->you] " + body + "\n");
                } else {
                    std::cout << "User not found: " << target << "\n";
                }
            } else {
                std::cout << "Invalid send format. Use @username message\n";
            }
            continue;
        }

        // broadcast
        broadcast("[server] " + line + "\n");
    }
    // shutdown all
    running = false;
}

void timeout_monitor(std::chrono::minutes timeout) {
    while (running) {
    std::this_thread::sleep_for(std::chrono::seconds(10));
        auto now = std::chrono::steady_clock::now();
        std::vector<int> to_close;
        {
            std::lock_guard<std::mutex> lock(clients_mutex);
            for (auto &p : last_activity) {
                auto diff = std::chrono::duration_cast<std::chrono::minutes>(now - p.second);
                if (diff >= timeout) {
                    to_close.push_back(p.first);
                }
            }
        }
        for (int s : to_close) {
            std::string name;
            {
                std::lock_guard<std::mutex> lock(clients_mutex);
                if (clients.count(s)) name = clients[s];
            }
            if (!name.empty()) {
                std::string msg = "[server] disconnected for inactivity\n";
                safe_send(s, msg);
            }
            remove_client(s);
            std::cout << "Disconnected " << name << " for inactivity\n";
        }
    }
}

int main(int argc, char **argv) {
    int port = DEFAULT_PORT;
    int timeout_minutes = DEFAULT_TIMEOUT_MINUTES;
    if (argc >= 2) port = std::stoi(argv[1]);
    if (argc >= 3) timeout_minutes = std::stoi(argv[2]);

    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    std::cout << "Server listening on port " << port << "..." << std::endl;
    std::cout << "Inactivity timeout set to " << timeout_minutes << " minutes." << std::endl;

    //print commands
    std::cout << "Available server commands:\n"
                << " - /list : list connected users\n"
                << " - /quit : shut down server\n"
                << " - /close username : disconnect user\n"
                << " - @username message : send direct message to username\n"
                << "Simply type and hit Enter to broadcast a message to all users.\n \n";

    // thread: server stdin handler
    std::thread input_thread(server_input_thread, server_fd);

    // thread: timeout monitor
    std::thread monitor_thread(timeout_monitor, std::chrono::minutes(timeout_minutes));

    // accept loop
    while (running) {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            if (!running) break;
            perror("accept");
            continue;
        }
        std::thread t(handle_client, new_socket);
        t.detach();
    }

    // shutdown
    running = false;
    close(server_fd);
    // close all client sockets
    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        for (auto &p : clients) {
            shutdown(p.first, SHUT_RDWR);
            close(p.first);
        }
        clients.clear();
    }

    if (input_thread.joinable()) input_thread.join();
    if (monitor_thread.joinable()) monitor_thread.join();

    std::cout << "Server exiting." << std::endl;
    return 0;
}
