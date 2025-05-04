#include <iostream>

using std::cout;
using std::endl;
using std::cin;

// abstract command
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

//receiver
class Eat {
public:
    void roisesOne() {
        cout << "mmm 11:30PM rosie's" << endl;
    }

    void roisesTwo() {
        cout << "mmm 12:00PM rosie's" << endl;
    }
};

// concrete command
class EatRosiesOne: public Command {
public:
    EatRosiesOne(Eat* eat) : eat_(eat) {}
    void execute() override {
        eat_->roisesOne();
    }
    ~EatRosiesOne() {delete eat_;}
private:
    Eat* eat_;
};

class EatRosiesTwo: public Command {
public:
    EatRosiesTwo(Eat* eat) : eat_(eat) {}
    void execute() override {
        eat_->roisesTwo();
    }
    ~EatRosiesTwo() {delete eat_;}
private:
    Eat* eat_;
};

// invoker
class Person { 
public:
    Person(Command *command) : command_(command) {}
    void setCommand(Command *command) {
        command_ = command;
    }
    void executeEat() {
        command_->execute();
    }
    ~Person() {delete command_;}
private:
    Command* command_;
};

//client code
int main() {
    Eat food;
    EatRosiesTwo R2(&food);
    EatRosiesOne R1(&food);

    Person person(&R1);
    person.executeEat();
    person.setCommand(&R2);
    person.executeEat();
}