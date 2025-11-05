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

const int DEFAULT_PORT = 8080;
const int DEFAULT_TIMEOUT_MINUTES = 2;

std::atomic<bool> running(true);
std::mutex last_activity_mutex;
std::chrono::steady_clock::time_point last_activity;

void update_activity() {
    std::lock_guard<std::mutex> lock(last_activity_mutex);
    last_activity = std::chrono::steady_clock::now();
}

void recv_thread_fn(int sock) {
    char buffer[1024];
    while (running) {
        ssize_t len = recv(sock, buffer, sizeof(buffer)-1, 0);
        if (len <= 0) break;
        buffer[len] = '\0';
        std::cout << buffer;
        std::cout << std::flush;
        update_activity();
    }
    running = false;
}

void timeout_monitor(int sock, std::chrono::minutes timeout) {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        std::chrono::steady_clock::time_point now;
        {
            std::lock_guard<std::mutex> lock(last_activity_mutex);
            now = std::chrono::steady_clock::now();
            auto diff = std::chrono::duration_cast<std::chrono::minutes>(now - last_activity);
            if (diff >= timeout) {
                std::cout << "[client] Inactivity timeout, closing connection\n";
                running = false;
                shutdown(sock, SHUT_RDWR);
                close(sock);
                break;
            }
        }
    }
}

int main(int argc, char **argv) {
    const char *server_ip = "127.0.0.1";
    int port = DEFAULT_PORT;
    int timeout_minutes = DEFAULT_TIMEOUT_MINUTES;
    if (argc >= 2) server_ip = argv[1];
    if (argc >= 3) port = std::stoi(argv[2]);
    if (argc >= 4) timeout_minutes = std::stoi(argv[3]);

    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return 1;
    }
    std::cout << "Connected to server at " << server_ip << ":" << port << std::endl;

    // ask username
    std::string username;
    std::cout << "Enter username: ";
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
            std::cout << "Connection closed by server while choosing username\n";
            close(sock);
            return 1;
        }
        buffer[len] = '\0';
        std::string resp(buffer);
        std::cout << resp; // show server message
        // server indicates username taken with this token
        if (resp.find("USERNAME_TAKEN") != std::string::npos || resp.find("username already in use") 
          != std::string::npos) {
            // prompt for a new username and resend
            std::cout << "Choose a different username: ";
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
    std::thread recv_thread(recv_thread_fn, sock);

    // start timeout monitor
    std::thread monitor_thread(timeout_monitor, sock, std::chrono::minutes(timeout_minutes));

    // main loop: poll stdin so we can exit promptly when disconnected
    struct pollfd pfd;
    pfd.fd = STDIN_FILENO;
    pfd.events = POLLIN;
    std::string line;
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

    std::cout << "Client exited." << std::endl;
    return 0;
}
