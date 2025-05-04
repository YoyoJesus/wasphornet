// Command Design Pattern

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

// receiver
class light {
public:
    void turn_on() {
        cout << "Light is ON" << endl;
    }
    void turn_off() {
        cout << "Light is OFF" << endl;
    }
};

// command interface
class command {
public:
    virtual void execute() = 0;
    virtual ~command() {}
};

// concrete command
class turnON : public command {
public:
    turnON(light* l) : light_(l) {}
    void execute() override {cout << "ON" << endl; light_->turn_on();}
    ~turnON() override {}
private:
    light* light_;
};

class turnOFF : public command {
public:
    turnOFF(light* l) : light_(l) {}
    void execute() override {cout << "OFF" << endl; light_->turn_off();}
    ~turnOFF() override {}
private:
    light* light_;
};

// invoker
class remote {
public:
    void set_command(command* c) {command_ = c;}
    void press_button() {cout << "button pressed "; command_->execute();}
    ~remote() {delete command_;}
private:
    command* command_;
};

// client code
int main() {
    light* l = new light();
    command* on = new turnON(l);
    command* off = new turnOFF(l);

    remote* r = new remote();
    r->set_command(on);
    r->press_button();

    r->set_command(off);
    r->press_button();

    delete r;
    delete l;
}