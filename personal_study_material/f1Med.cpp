#include <iostream>
#include <deque>
#include <set>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <memory>

using namespace std;

// abstract mediator
class Control {
public:
    virtual void join(class Car* car) = 0;
    virtual void leave(class Car* car) = 0;
    virtual void notify() = 0;
    virtual void observe() = 0;
};

// concrete mediator
class RaceControl : public Control {
public:
    void join(class Car* car) override {
        waitingCars_.insert(car);
    }

    void leave(class Car* car) override {
        waitingCars_.erase(car);
    }

    void notify() override;
    void observe() override;
private:
    set<class Car*> waitingCars_;
};

// abstract colleague
class Car {
public:
    Car(string driver, Control *controller) : carDriver_(driver), controller_(controller), 
            carStatus_(CarStatus::waiting), 
            carState_(rand() % 2 == 0 ? CarState::READY : CarState::STOPPED) {
        controller_->join(this);
    }
    void receive(const string &message) {
        if (message.find(carDriver_) != string::npos || message.find("all") != string::npos) { 
            if (message.find("go") != string::npos) {
                cout << carDriver_ << " received: " << message << endl;
                cout << (carState_ == CarState::READY ? "Ready" : "Stopped") << endl;
                carStatus_ = CarStatus::racing;
            } else if(message.find("status") != string::npos) {
                cout << carDriver_ << " received: " << message << endl;
                cout << (carState_ == CarState::READY ? "Ready" : "Stopped") << endl;
                carStatus_ = CarStatus::waiting;
            } else {
                cout << "This is " << carDriver_ << " please repeat" << endl;
            }
        }
    }
    bool isRacing() {
        return carStatus_ == CarStatus::racing;
    }
    void proceed() {
        this_thread::sleep_for(chrono::seconds(rand() % 3 + 1));
        cout << carDriver_ << (carState_ == CarState::READY ? " is ready" : " is stopped") <<
            " and is excited to race" << endl;
        controller_->leave(this);
    }
protected:
    string carDriver_;
    Control *controller_;
    enum class CarState { READY, STOPPED }; CarState carState_;
    enum class CarStatus {waiting, racing}; CarStatus carStatus_;
};

// concrete colleague
class Mclaren : public Car {
public:
    Mclaren(Control *controller) : Car(rand() % 2 == 0 ? "Lando" : "Oscar", controller) {
        carState_ = rand() % 2 == 0 ? CarState::READY : CarState::STOPPED;
        cout << carDriver_ << " is " << (carState_ == CarState::READY ? "ready" : "stopped") << endl;
    }
};

class Mercedes : public Car {
public:
    Mercedes(Control *controller) : Car(rand() % 2 == 0 ? "Kimi" : "George", controller) {
        carState_ = rand() % 2 == 0 ? CarState::READY : CarState::STOPPED;
        cout << carDriver_ << " is " << (carState_ == CarState::READY ? "ready" : "stopped") << endl;
    }
};

void RaceControl::notify() {
    cout << "Control: ";
    string msg;
    getline(cin, msg);
    if (!msg.empty()) {
        for (auto car : waitingCars_) {
            car->receive(msg);
        }
    }
}

void RaceControl::observe() {
    auto findCleared = [](Car* car) {
        return car->isRacing();
    };

    auto toProceed = std::find_if(waitingCars_.begin(), waitingCars_.end(), findCleared);

    while (toProceed != waitingCars_.end()) {
        (*toProceed)->proceed();
        toProceed = std::find_if(waitingCars_.begin(), waitingCars_.end(), findCleared);
        if (toProceed != waitingCars_.end()) {
            cout << "CRASHED" << endl;
        }
    }
}

//client code
int main() {
    srand(time(nullptr));
    RaceControl raceControl;

    new Mclaren(&raceControl);
    new Mercedes(&raceControl);

    while (true) {
        raceControl.notify();
        raceControl.observe();
        if (rand() % 2 == 0)
            new Mclaren(&raceControl);
        else
            new Mercedes(&raceControl);

        // Add a termination condition if needed
    }
}
