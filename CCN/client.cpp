#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>
#include <string>
#include <sstream>
#include <cstdlib>
#include <poll.h>

using std::string; using std::cout; using std::endl;
using std::thread; using std::mutex; using std::lock_guard;

const int PORT = 8080;
const int TIMEOUT_MINUTES = 2;

// tag formatting: match server tag width for uniform output (7 chars inside brackets)
static const int TAG_WIDTH = 7;
static std::string pad_tag(const std::string &t) {
    int inner_width = TAG_WIDTH;
    int max_tag_len = inner_width - 2; // reserve one space on each side inside brackets
    std::string tx = t;
    if ((int)tx.size() > max_tag_len) tx = tx.substr(0, max_tag_len);
    int total_pad = max_tag_len - (int)tx.size();
    int left_pad = total_pad / 2;
    int right_pad = total_pad - left_pad;
    return std::string("[") + std::string(" ") + std::string(left_pad, ' ') + tx + std::string(right_pad, ' ') + std::string(" ") + std::string("] ");
}

std::atomic<bool> running(true);
mutex last_activity_mutex;
std::chrono::steady_clock::time_point last_activity;

void update_activity() {
    lock_guard<mutex> lock(last_activity_mutex);
    last_activity = std::chrono::steady_clock::now();
}

void recv_thread_fn(int sock) {
    char buffer[1024];
    while (running) {
        ssize_t len = recv(sock, buffer, sizeof(buffer)-1, 0);
        if (len <= 0) break;
        buffer[len] = '\0';
        std::string s(buffer);
        cout << s;
        // if server announces shutdown or authorizes shutdown, exit promptly
        if (s.find("Shutdown authorized") != std::string::npos || s.find("Server is shutting down") != std::string::npos) {
            // give user the server message, then exit
            cout << std::flush;
            running = false;
            shutdown(sock, SHUT_RDWR);
            close(sock);
            break;
        }
        cout << std::flush;
        update_activity();
    }
    running = false;
}

void timeout_monitor(int sock, std::chrono::minutes timeout) {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::chrono::steady_clock::time_point now;
        {
            lock_guard<mutex> lock(last_activity_mutex);
            now = std::chrono::steady_clock::now();
            auto diff = std::chrono::duration_cast<std::chrono::minutes>(now - last_activity);
            if (diff >= timeout) {
                cout << pad_tag("CLIENT") << "Inactivity timeout, closing connection\n";
                running = false;
                shutdown(sock, SHUT_RDWR);
                close(sock);
                break;
            }
        }
    }
}

int main() {
    const char *server_ip = "127.0.0.1";

    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return 1;
    }
    cout << "Connected to server at " << server_ip << ":" << PORT << endl;

    // ask username
    string username;
    cout << "Enter username: ";
    std::getline(std::cin, username);
    if (username.empty()) username = "guest";
    // send username as first message
    send(sock, username.c_str(), username.size(), 0);
    update_activity();

    // wait for server acceptance or USERNAME_TAKEN response before starting recv thread
    char buffer[1024];
    while (true) {
        ssize_t len = recv(sock, buffer, sizeof(buffer)-1, 0);
        if (len <= 0) {
            cout << "Connection closed by server while choosing username\n";
            close(sock);
            return 1;
        }
        buffer[len] = '\0';
        string resp(buffer);
        cout << resp; // show server message
        // server indicates username taken with this token
        if (resp.find("USERNAME_TAKEN") != string::npos || resp.find("username already in use") 
          != string::npos) {
            // prompt for a new username and resend
            cout << "Choose a different username: ";
            std::getline(std::cin, username);
            if (username.empty()) username = "guest";
            send(sock, username.c_str(), username.size(), 0);
            update_activity();
            continue;
        }
        // otherwise assume accepted (server sends a Welcome message)
        break;
    }

    // start receiver thread
    thread recv_thread(recv_thread_fn, sock);

    // start timeout monitor
    thread monitor_thread(timeout_monitor, sock, std::chrono::minutes(TIMEOUT_MINUTES));

    // main loop: poll stdin so we can exit promptly when disconnected
    struct pollfd pfd;
    pfd.fd = STDIN_FILENO;
    pfd.events = POLLIN;
    string line;
    while (running) {
        int pret = poll(&pfd, 1, 500); // 500 ms
        if (!running) break;
        if (pret > 0) {
            if (pfd.revents & POLLIN) {
                if (!std::getline(std::cin, line)) {
                    // EOF on stdin
                    break;
                }
                if (line.empty()) continue;
                if (line == "/quit") {
                    send(sock, line.c_str(), line.size(), 0);
                    running = false;
                    break;
                }
                if (line == "/list") {
                    send(sock, line.c_str(), line.size(), 0);
                    update_activity();
                    continue;
                }
                ssize_t sent = send(sock, line.c_str(), line.size(), 0);
                (void)sent;
                update_activity();
            }
        } else if (pret == 0) {
            // timeout, just check running again
            continue;
        } else {
            // poll error
            break;
        }
    }

    running = false;
    shutdown(sock, SHUT_RDWR);
    close(sock);

    if (recv_thread.joinable()) recv_thread.join();
    if (monitor_thread.joinable()) monitor_thread.join();

    cout << "Client exited." << endl;
    return 0;
}
