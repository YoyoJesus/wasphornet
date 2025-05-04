// adapter
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// target
class Car {
public:
    virtual void drive() = 0;
    virtual void setTeam(const string& team) = 0;
    virtual string getTeam() const = 0;
protected:
    string team_;
};


// adaptee
class F1Car {
public:
    F1Car(string name, int speed, string driver = "")
        : name_(name), speed_(speed), driver_(driver) {}

    void drive() {
        cout << driver_ << " driving F1 car: " << name_ << " at speed: " << speed_ << endl;
    }
    void setDriver(const string& driver) {
        driver_ = driver;
    }
    string getDriver() const {
        return driver_;
    }
    string getName() const {
        return name_;
    }
    int getSpeed() const {
        return speed_;
    }
    void setSpeed(int speed) {
        speed_ = speed;
    }
    void setName(const string& name) {
        name_ = name;
    }
    void setDriverName(const string& driver) {
        driver_ = driver;
    }
    string getDriverName() const {
        return driver_;
    }
private:
    string name_;
    int speed_;
    string driver_;
};

// adapter
class F1CarAdapter: private F1Car, public Car {
public:
    F1CarAdapter(const string& team, int speed) : F1Car("MCL39", speed, "KIMI") { team_ = team; }

    void drive() override {
        F1Car::drive();
    }

    void setTeam(const string& team) override {
        team_ = team;
    }

    string getTeam() const override {
        return team_;
    }
};

// client
int main() {
    F1CarAdapter f1Car("Ferrari", 200);
    f1Car.drive();
    cout << "Team: " << f1Car.getTeam() << endl;

    f1Car.setTeam("Mercedes");
    cout << "New Team: " << f1Car.getTeam() << endl;
}
