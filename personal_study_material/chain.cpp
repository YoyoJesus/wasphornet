#include <iostream>
#include <string>
#include <vector>

using namespace std;

// administrator - abstract handler
class FIA {
public:
    FIA(FIA *successor = nullptr) : successor_(successor) {}
    virtual void handleRequest(const string& request) {
        if (successor_) {
            successor_->handleRequest(request);
        } else {
            cout << "No one can handle the request: " << request << endl;
        }
    }
private:
    FIA *successor_;
};

// concrete handlers
class RaceDirector : public FIA {
public:
    RaceDirector(FIA *successor = nullptr) : FIA(successor) {}
    void handleRequest(const string& request) override {
        if (request == "PEREZ" || request == "VERSTAPPEN") {
            cout << "10 seconds penalty for " << request << "Handled by RaceDirector" << endl;
        } else {
            FIA::handleRequest(request);
        }
    }
};

class RaceSteward : public FIA {
public:
    RaceSteward(FIA *successor = nullptr) : FIA(successor) {}
    void handleRequest(const string& request) override {
        if (request == "LECLERC" || request == "SAINZ") {
            cout << "5 seconds penalty for " << request << endl;
        } else {
            FIA::handleRequest(request);
        }
    }
};

class RaceControl : public FIA {
public:
    RaceControl(FIA *successor = nullptr) : FIA(successor) {}
    void handleRequest(const string& request) override {
        if (request == "HAMILTON" || request == "RUSSELL") {
            cout << "3 seconds penalty for " << request << endl;
        } else {
            FIA::handleRequest(request);
        }
    }
};

//client code
int main() {
    FIA *raceStaff = new RaceControl(new RaceSteward(new RaceDirector()));

    vector<string> requests = {"PEREZ", "LECLERC", "HAMILTON", "VERSTAPPEN", "SAINZ", "RUSSELL", "ALONSO"};
    for (int i = 0; i < requests.size(); ++i) {
        raceStaff->handleRequest(requests[i]);
    }
}