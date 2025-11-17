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
#include <ctime>
#include <random>

using std::string; using std::cout; using std::endl;
using std::thread; using std::mutex; using std::lock_guard;

const int PORT = 8080;
const int TIMEOUT_MINUTES = 2;

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

std::atomic<bool> running(true);

void recv_thread_fn(int sock) {
    char buffer[1024];
    while (running) {
        ssize_t len = recv(sock, buffer, sizeof(buffer)-1, 0);
        if (len <= 0) break;
        buffer[len] = '\0';
        string s(buffer);
        cout << s;
        // if server announces shutdown or authorizes shutdown, exit promptly
        if (s.find("Shutdown authorized") != string::npos || s.find("Server is shutting down") != string::npos) {
            // give user the server message, then exit
            cout << std::flush;
            running = false;
            shutdown(sock, SHUT_RDWR);
            close(sock);
            break;
        }
        cout << std::flush;
    }
    running = false;
}

string build_guest_username() {
    // generate a random guest username
    // guestXXX where XXX is a random number 100-999
    int r = rand() % 900 + 100;
    return "guest" + std::to_string(r);
}

int main() {
    const char *server_ip = "127.0.0.1";
    srand(time(nullptr));

    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    // populate server IP
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return 1;
    }
    cout << "Connected to server at " << server_ip << ":" << PORT << endl;

    // ask username
    string username;
    cout << "Enter username: ";
    std::getline(std::cin, username);
    if (username.empty()) username = build_guest_username();
    // send username as first message
    send(sock, username.c_str(), username.size(), 0);

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
            continue;
        }
        // otherwise assume accepted (server sends a Welcome message)
        break;
    }

    // start receiver thread
    thread recv_thread(recv_thread_fn, sock);

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
                    continue;
                }
                ssize_t sent = send(sock, line.c_str(), line.size(), 0);
                (void)sent;
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

    cout << "Client exited." << endl;
    return 0;
}
