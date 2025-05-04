// bridge design pattern
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::cin;

// abstract body
class Electronic{
public:
    Electronic(const string& name) : name_(name) {}
    virtual void run() = 0;
    virtual void stop() = 0;
    virtual string getStatus() = 0;
    void report() {
        cout << "Status: " << getStatus() << endl;
    }
    virtual ~Electronic() {}
private:
    string name_;
};

// concrete body
class TV : public Electronic {
public:
    TV(const string& name): Electronic(name) {}
    void run() override {status_ = "TV is on"; channel_ = "ABC";}
    void stop() override {status_ = "TV is off"; channel_ = "";}
    string getStatus() override {return status_ + (channel_.empty() ? "" : " on channel " + channel_);}
private:
    string status_;
    string channel_;
};

class Radio : public Electronic {
public:
    Radio(const string& name) : Electronic(name) {}
    void run() override {status_ = "Radio is on";}
    void stop() override {status_ = "Radio is off";}
    string getStatus() override {return status_;}
private:
    string status_;
};

//abstract handle
class switcher{
public:
    switcher(const string& name, Electronic *control) : name_(name), controls_(control) {}
    void turnOn() {cout << name_ << " turns on" << endl; controls_->run();}
    void turnOff() {cout << name_ << " turns off" << endl; controls_->stop();}
    virtual ~switcher() {}
protected:
    Electronic *controls_;
private:
    string name_;
};

// concrete handle
class Remote : public switcher {
public:
    Remote(const string& name, Electronic *device) : switcher(name, device) {}
};

class WallSwitch : public switcher {
public:
    WallSwitch(const string& name, Electronic *device) : switcher(name, device) {}
};

// client code
int main() {
    Electronic *tv = new TV("Bedroom TV");
    Electronic *radio = new Radio("Kitchen Radio");

    switcher *remote = new Remote("Bedroom Remote", tv);
    remote->turnOn(); tv->report();
    remote->turnOff(); tv->report();

    switcher *wallSwitch = new WallSwitch("Kitchen Wall Switch", radio);
    wallSwitch->turnOn(); radio->report();
    wallSwitch->turnOff(); radio->report();

    //show that a either switch can control either device
    remote = new Remote("Kitchen Remote", radio);
    remote->turnOn(); radio->report();
    remote->turnOff(); radio->report();
    delete remote;

    wallSwitch = new WallSwitch("Bedroom Wall Switch", tv);
    wallSwitch->turnOn(); tv->report();
    wallSwitch->turnOff(); tv->report();
    delete wallSwitch;


    delete tv;
    delete radio;
}