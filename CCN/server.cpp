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
#include <cstdlib>

using std::string; using std::cout; using std::endl;
using std::thread; using std::mutex; using std::lock_guard;
using std::map; using std::vector;

// logging
mutex log_mutex;
void server_log(const string &msg) {
    lock_guard<mutex> lg(log_mutex);
    cout << msg << endl;
}

static const int TAG_WIDTH = 6;
static string pad_tag(const string &t) {
    const string tx = t;
    const int width = TAG_WIDTH;
    if ((int)tx.size() >= width) {
        return string("[") + tx + string("] ");
    }
    int total_pad = width - (int)tx.size();
    int left_pad = total_pad / 2;
    int right_pad = total_pad - left_pad;
    return string("[") + string(left_pad, ' ') + tx + string(right_pad, ' ') + string("] ");
}

// default port number is 8080 for simplicity
const int PORT = 8080;
// default inactivity timeout in minutes
const int TIMEOUT_MINUTES = 2;

map<int, string> clients; // sock -> username
map<int, std::chrono::steady_clock::time_point> last_activity;
mutex clients_mutex;
std::atomic<bool> running(true);
int server_fd = -1;

// forward declarations needed for initiate_shutdown
void broadcast(const string &msg, int except_sock);

// centralized shutdown routine so both operator and authorized clients use the same code path
void initiate_shutdown(const string &initiator) {
    // announce
    string notice = pad_tag("SERVER") + "Server is shutting down\n";
    if (initiator != "operator") {
        notice += "initiated by " + initiator + " with elevated permissions\n";
    } else {
        notice += " communications. Goodbye!\n";
    }
    broadcast(notice, -1);
    if (initiator != "operator") {
        server_log(pad_tag("SERVER") + "Shutdown initiated by " + initiator);
    } else {
        server_log(pad_tag("SERVER") + "Shutdown initiated" );
    }
    // close all client sockets
    {
        lock_guard<mutex> lock(clients_mutex);
        for (auto &p : clients) {
            int s = p.first;
            if (s > 0) {
                shutdown(s, SHUT_RDWR);
                close(s);
            }
        }
        clients.clear();
        last_activity.clear();
    }
    // flip running and close listening socket
    running = false;
    if (server_fd != -1) {
        shutdown(server_fd, SHUT_RDWR);
        close(server_fd);
        server_fd = -1;
    }
    _exit(EXIT_SUCCESS); //terminate server process
}

void safe_send(int sock, const string &msg) {
    if (sock <= 0) return;
    ssize_t sent = send(sock, msg.c_str(), msg.size(), 0);
    (void)sent;
}

void broadcast(const string &msg, int except_sock = -1) {
    lock_guard<mutex> lock(clients_mutex);
    for (auto &p : clients) {
        int s = p.first;
        if (s == except_sock) continue;
        safe_send(s, msg);
        server_log(pad_tag("SENT") + "to " + p.second + " (sock " + std::to_string(s) + ") : " + msg);
    }
}

int find_sock_by_username(const string &username) {
    lock_guard<mutex> lock(clients_mutex);
    for (auto &p : clients) {
        if (p.second == username) return p.first;
    }
    return -1;
}

void remove_client(int sock) {
    string name;
    {
        lock_guard<mutex> lock(clients_mutex);
        auto it = clients.find(sock);
        if (it != clients.end()) {
            name = it->second;
            clients.erase(it);
            last_activity.erase(sock);
        }
    }
    if (!name.empty()) {
        string notice = pad_tag("SERVER") + name + " disconnected\n";
        broadcast(notice, -1);
        //cout << pad_tag("SERVER") << "ALERT: " << name << " disconnected (socket " << sock << ")" << endl;
    }
    shutdown(sock, SHUT_RDWR);
    close(sock);
}

void handle_client(int client_sock) {
    char buffer[1024];
    ssize_t len = recv(client_sock, buffer, sizeof(buffer)-1, 0);
    if (len <= 0) {
        close(client_sock);
        return;
    }
    buffer[len] = '\0';
    string username(buffer);
    if (!username.empty() && username.back() == '\n') username.pop_back();

    // allow the client to retry usernames until a unique one is chosen
    while (true) {
        bool duplicate = false;
        {
            lock_guard<mutex> lock(clients_mutex);
            for (auto &p : clients) {
                if (p.second == username) { duplicate = true; break; }
            }
        }
        if (!duplicate) break;

      // inform client the username is taken and ask for a new one
      safe_send(client_sock, pad_tag("SERVER") + "USERNAME IS TAKEN\n");
      server_log(pad_tag("REJECT") + "connection attempt with duplicate username: " 
          + username + " (sock " + std::to_string(client_sock) + ")");

        // wait for the client to send a different username
        ssize_t r = recv(client_sock, buffer, sizeof(buffer)-1, 0);
        if (r <= 0) { shutdown(client_sock, SHUT_RDWR); close(client_sock); return; }
        buffer[r] = '\0';
        username = string(buffer);
        if (!username.empty() && username.back() == '\n') username.pop_back();
    }
    {
        lock_guard<mutex> lock(clients_mutex);
        clients[client_sock] = username;
        last_activity[client_sock] = std::chrono::steady_clock::now();
    }
    string join_msg = pad_tag("SERVER") + username + " joined\n";
    broadcast(join_msg, client_sock);
    safe_send(client_sock, pad_tag("SERVER") + "Welcome, " + username + "\n" + "Available commands:\n" 
        + " - /list : list connected users\n"
        + " - /quit : disconnect\n"
        + " - @username message : send direct message to username or usernames (comma-separated)\n" 
        + " - /shutdown <password> : shut down server (authorized users only)\n"
        + "Type your message and hit Enter to broadcast to all users.\n\n");
    //cout << pad_tag("SERVER") << "ALERT: " << username << " joined (socket " << client_sock << ")" << endl;
    // log join event
    server_log(pad_tag("JOIN") + username + " (sock " + std::to_string(client_sock) + ")");

    while (running) {
        len = recv(client_sock, buffer, sizeof(buffer)-1, 0);
        if (len <= 0) break; // disconnect or error
    buffer[len] = '\0';
    string msg(buffer);
    server_log(pad_tag("RX") + "from " + username + " (sock " + std::to_string(client_sock) + ") : " + msg);
        // trim newline at end
        while (!msg.empty() && (msg.back() == '\n' || msg.back() == '\r')) msg.pop_back();

        // normalize common accidental leading slash before DM, e.g. '/@alice hi' -> '@alice hi'
        if (msg.size() >= 2 && msg[0] == '/' && msg[1] == '@') {
            msg.erase(0, 1);
        }

        // update activity
        {
            lock_guard<mutex> lock(clients_mutex);
            last_activity[client_sock] = std::chrono::steady_clock::now();
        }

        // allow privileged shutdown from client: format "/shutdown <password>"
        if (msg.rfind("/shutdown", 0) == 0) {
            // parse password (if provided)
            string pw;
            size_t sp = msg.find(' ');
            if (sp != string::npos) pw = msg.substr(sp+1);
            if (pw == "admin123") { // hardcoded password for simplicity, I know this is insecure
                // authorized: ack and use centralized shutdown routine
                safe_send(client_sock, pad_tag("SERVER") + "Shutdown authorized\n");
                initiate_shutdown(username);
                break;
            } else {
                safe_send(client_sock, pad_tag("SERVER") + "Invalid password\n");
                continue;
            }
        }

        if (msg == "/quit" || msg == "/close") {
            safe_send(client_sock, pad_tag("SERVER") + "Goodbye\n");
            break;
        }

        if (msg == "/list") {
            std::ostringstream oss;
            oss << pad_tag("SERVER") << "Connected users:\n";
            lock_guard<mutex> lock(clients_mutex);
            for (auto &p : clients) {
                oss << " - " << p.second << "\n";
            }
            safe_send(client_sock, oss.str());
            continue;
        }

        // direct/multicast syntax: one or more @username tokens (or comma-separated) followed by message
        if (!msg.empty() && msg[0] == '@') {
            // parse targets (support @alice @bob msg or @alice,bob msg)
            vector<string> targets;
            size_t pos = 0;
            while (pos < msg.size() && msg[pos] == '@') {
                size_t space_pos = msg.find(' ', pos);
                string token;
                if (space_pos != string::npos) {
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
                    string name = (comma == string::npos) ? token.substr(start) : token.substr(start, comma - start);
                    if (!name.empty()) targets.push_back(name);
                    if (comma == string::npos) break;
                    start = comma + 1;
                }
                // skip any spaces
                while (pos < msg.size() && msg[pos] == ' ') pos++;
                // if next char isn't '@' then we've consumed the target list
                if (pos >= msg.size() || msg[pos] != '@') break;
            }

            // remaining is body
            string body;
            if (pos < msg.size()) body = msg.substr(pos);
            // trim leading spaces
            while (!body.empty() && body.front() == ' ') body.erase(body.begin());

            string sender;
            {
                lock_guard<mutex> lock(clients_mutex);
                sender = clients[client_sock];
            }

            if (targets.empty()) {
                safe_send(client_sock, pad_tag("SERVER") + "Invalid direct message format. Use @username message\n");
                continue;
            }


            // deduplicate targets
            std::sort(targets.begin(), targets.end());
            targets.erase(std::unique(targets.begin(), targets.end()), targets.end());

            // deliver to each target, collect missing targets
            vector<string> missing;
            vector<string> delivered;
            for (auto &t : targets) {
                int tsock = find_sock_by_username(t);
                if (tsock == -1) {
                    missing.push_back(t);
                } else {
                    safe_send(tsock, pad_tag("DM") + sender + ": " + body + "\n");
                    delivered.push_back(t);
                    server_log(pad_tag("MCAST") + "from " + sender + " (sock " + std::to_string(client_sock) + ") to " + t + " (sock " + std::to_string(tsock) + ") : " + body);
                }
            }

            // acknowledge to sender
            if (!delivered.empty()) {
                std::ostringstream ack;
                // construct a compact dm->recipient list and then pad the whole tag
                string delivered_list;
                for (size_t i = 0; i < delivered.size(); ++i) {
                    if (i) delivered_list += ",";
                    delivered_list += delivered[i];
                }
                // build ack using a compact DM tag; put recipients outside the bracket
                ack << pad_tag("DM") << "->" << delivered_list << " " << body << "\n";
                safe_send(client_sock, ack.str());
            }
            if (!missing.empty()) {
                std::ostringstream miss;
                miss << pad_tag("SERVER") << "user(s) not found:";
                for (auto &m : missing) miss << ' ' << m;
                miss << "\n";
                safe_send(client_sock, miss.str());
            }

            continue;
        }

        // broadcast otherwise
        string sender;
        {
            lock_guard<mutex> lock(clients_mutex);
            sender = clients[client_sock];
        }
    string out = sender + ": " + msg + "\n";
    // log broadcast intent
    server_log(pad_tag("BCAST") + "from " + sender + " (sock " + std::to_string(client_sock) + ") : " + msg);
    broadcast(out, client_sock);
    // acknowledge to sender that their message was broadcast
    safe_send(client_sock, pad_tag("BCAST") + "->all " + msg + "\n");
    }

    remove_client(client_sock);
}

void server_input_thread(int server_sock) {
    string line;
    while (running && std::getline(std::cin, line)) {
        if (line.empty()) continue;
        if (line == "/shutdown") {
            // centralized shutdown (operator invoked)
            initiate_shutdown("operator");
            break;
        }
        if (line == "/list") {
            lock_guard<mutex> lock(clients_mutex);
            cout << "Connected users:\n";
            for (auto &p : clients) cout << " - " << p.second << "\n";
            continue;
        }
        if (line == "/dump_activity") {
            lock_guard<mutex> lock(clients_mutex);
            auto now = std::chrono::steady_clock::now();
            cout << "Tracked activity for " << last_activity.size() << " entries:\n";
            for (auto &p : last_activity) {
                int sock = p.first;
                auto age = std::chrono::duration_cast<std::chrono::seconds>(now - p.second).count();
                string name = "";
                if (clients.count(sock)) name = clients[sock];
                if (!name.empty()) {
                    cout << " - " << name << " (sock " << sock << ") : " << age << "s since last activity\n";
                } else {
                    cout << " - socket " << sock << " : " << age << "s since last activity\n";
                }
            }
            continue;
        }
        // close a user's connection: /close username
        if (line.rfind("/close ", 0) == 0) {
            string u = line.substr(7);
            int s = find_sock_by_username(u);
                if (s != -1) {
                    safe_send(s, pad_tag("SERVER") + "You have been disconnected by server\n");
                    remove_client(s);
                    cout << "Closed connection for " << u << "\n";
                } else {
                    cout << "User not found: " << u << "\n";
                }
            continue;
        }

        // send to user: @username message
        if (line[0] == '@') {
            auto sp = line.find(' ');
            if (sp != string::npos) {
                string target = line.substr(1, sp-1);
                string body = line.substr(sp+1);
                int s = find_sock_by_username(target);
                if (s != -1) {
                    safe_send(s, pad_tag("SERVER->you") + body + "\n");
                } else {
                    cout << "User not found: " << target << "\n";
                }
            } else {
                cout << "Invalid send format. Use @username message\n";
            }
            continue;
        }

        // broadcast
        broadcast(pad_tag("SERVER") + line + "\n");
        // confirmation to server operator that a broadcast was sent
        cout << pad_tag("BCAST") << "->all " << line << endl;
    }
    // shutdown all
    running = false;
}

void timeout_monitor(std::chrono::minutes timeout) {
    while (running) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
        auto now = std::chrono::steady_clock::now();
        vector<int> to_close;
        {
            lock_guard<mutex> lock(clients_mutex);
            for (auto &p : last_activity) {
                // compare durations directly to avoid truncation to whole minutes
                if ((now - p.second) >= timeout) {
                    to_close.push_back(p.first);
                }
            }
        }
        for (int s : to_close) {
            string name;
            {
                lock_guard<mutex> lock(clients_mutex);
                if (clients.count(s)) name = clients[s];
            }
            if (!name.empty()) {
                string msg = pad_tag("serv") + "disconnected for inactivity\n";
                safe_send(s, msg);
            }
            remove_client(s);
            server_log(pad_tag("TMOUT") + "Disconnected " + name + "(socket " + std::to_string(s) + ") for inactivity\n");
        }
    }
}

int main() {
    // use the global server_fd declared above so initiate_shutdown can close it
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
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    cout << "Server listening on port " << PORT << "..." << endl;
    cout << "Inactivity timeout set to " << TIMEOUT_MINUTES << " minutes." << endl;

    //print commands
    cout << "Available server commands:\n"
                << " - /list : list connected users\n"
                << " - /shutdown : shut down server\n"
                << " - /close username : disconnect user\n"
                << " - @username message : send direct message to username\n"
                << " - /dump_activity : show last activity timestamps for all users\n"
                << "Simply type and hit Enter to broadcast a message to all users.\n \n";

    // thread: server stdin handler
    thread input_thread(server_input_thread, server_fd);

    // thread: timeout monitor
    thread monitor_thread(timeout_monitor, std::chrono::minutes(TIMEOUT_MINUTES));

    // accept loop
    while (running) {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            if (!running) break;
            perror("accept");
            continue;
        }
        thread t(handle_client, new_socket);
        t.detach();
    }

    initiate_shutdown("main");
}
