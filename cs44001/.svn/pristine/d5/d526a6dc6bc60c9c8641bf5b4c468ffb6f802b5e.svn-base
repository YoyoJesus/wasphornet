#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using std::cout; using std::endl;
using std::string;

class Logger {
public:
    // Meyer's singleton - way easier to implement
    static Logger& instance () {
        static Logger log;
        return log;
    }

    void report(const string &append) {
        file << append << std::endl;
    }

    ~Logger() {
        cout << "Logger destroyed" << endl;
        file.close();
    }

    // delete copy constructor and assignment operator - force singleton
    Logger& operator=(const Logger&) = delete;
    Logger(const Logger&) = delete;
private:
    Logger() {
        cout << "Logger created" << endl;
    }

    // making the file stream private - singleton won't cause file to be opened multiple times
    std::ofstream file{"log.txt", std::ios::app};
};


// Logger Function 1
void logonLog (string username, string password = "") {
    Logger::instance().report("User " + username + " logged on, password: " + password);

    // I am aware that you really shouldn't be logging passwords, but this is just a demo
    // and I don't want to make it too complicated. In a real application, you would
    // want to hash the password and store it securely, not log it in plain text.
}

// Logger Function 2
void incidentLog () {
    srand(time(0)); // seed the random number generator
    // report a malware attack
    string incident = "Malware attack detected";
    int incidentID = rand() % 1000;
    Logger::instance().report(incident + " - ID: " + std::to_string(incidentID));

}

int main() {
    // User logon
    logonLog("Alice");
    logonLog("Bob", "password123");
    logonLog("Charlie", "hackme");

    // Incident log 
    for (int i = 0; i < 5; ++i) {
        if (i % 2 == 0) incidentLog();
    }
    return 0;
}