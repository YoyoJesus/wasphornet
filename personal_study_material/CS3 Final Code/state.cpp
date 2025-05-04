//state design pattern

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::string;

//forward declaration
class State;

//context
class Person {
public:
    Person();

    void skipSleep();
    void Sleep();

    string report();

    void changeState(State* state){state_ = state;}
private:
    State* state_;
};

// abstract state
class State {
public:
    virtual void skipSleep(Person* person) {}
    virtual void Sleep(Person* person) {}
    virtual string report() = 0;

    void changeState(Person* person, State* state) {
        person->changeState(state);
    }
};

// concrete states
class Rested : public State {
public:
    static State* instance() {
        static State* instance = new Rested;
        return instance;
    }

    void skipSleep(Person*) override;
    void Sleep(Person*) override;
    string report() override {return "Rested";}
private:
    Rested& operator=(const Rested&) {}
    Rested(const Rested&) {}
    Rested() {}
};

class Tired : public State {
public:
    static State* instance() {
        static State* instance = new Tired;
        return instance;
    }

    void skipSleep(Person*) override;
    void Sleep(Person*) override;
    string report() override {return "Tired";}
private:
    Tired& operator=(const Tired&) {}
    Tired(const Tired&) {}
    Tired() {}
};

class Dead : public State {
public:
    static State* instance() {
        static State* instance = new Dead;
        return instance;
    }

    string report() override {return "Dead";}
private:
    Dead& operator=(const Dead&) {}
    Dead(const Dead&) {}
    Dead() {}
};

// implementation of Person methods
void Rested::skipSleep(Person* person) {
    changeState(person, Tired::instance());
}

void Rested::Sleep(Person* person) {
    changeState(person, Dead::instance());
}

void Tired::skipSleep(Person* person) {
    changeState(person, Dead::instance());
}

void Tired::Sleep(Person* person) {
    changeState(person, Rested::instance());
}

// implementation of Person methods
Person::Person() {state_ = Rested::instance();}

// handles/behaviors
void Person::skipSleep() {state_->skipSleep(this);}
void Person::Sleep() {state_->Sleep(this);}
string Person::report() {return state_->report();}

//client code
int main() {
    Person me;
    cout << "I am " << me.report() << endl;

    while (me.report() != "Dead") {
        cout << "Do you want to skip sleep? (y/n) ";
        char choice;
        cin >> choice;

        if (choice == 'y') {
            me.skipSleep();
        } else {
            me.Sleep();
        }

        cout << "I am " << me.report() << endl;
    }
}