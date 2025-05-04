// Mediator Design Pattern (Corrected Version)

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// Forward declaration
class Colleague;

// Abstract mediator class
class Mediator {
public:
    virtual void join(Colleague* colleague) = 0;
    virtual void leave(Colleague* colleague) = 0;
    virtual void broadcast(Colleague* sender) = 0;
};

// Abstract colleague class
class Colleague {
public:
    Colleague(Mediator* mediator) : mediator_(mediator) {}
    virtual void send() = 0;
    virtual void receive() = 0;
protected:
    Mediator* mediator_;
};

// Concrete mediator class
class ConcreteMediator : public Mediator {
public:
    void join(Colleague* colleague) override {
        colleagues_.push_back(colleague);
    }

    void leave(Colleague* colleague) override {
        auto it = std::remove(colleagues_.begin(), colleagues_.end(), colleague);
        if (it != colleagues_.end()) {
            colleagues_.erase(it, colleagues_.end());
        }
    }

    void broadcast(Colleague* sender) override {
        cout << "Mediator relaying message from a colleague...\n";
        for (auto colleague : colleagues_) {
            if (colleague != sender) {
                colleague->receive();
            }
        }
    }

private:
    vector<Colleague*> colleagues_;
};

// Concrete colleague classes
class ConcreteColleague : public Colleague {
public:
    ConcreteColleague(Mediator* mediator, const string& name)
        : Colleague(mediator), name_(name) {}

    void send() override {
        cout << name_ << " is sending a message...\n";
        mediator_->broadcast(this);
    }

    void receive() override {
        cout << name_ << " received a message.\n";
    }

private:
    string name_;
};

class ConcreteColleague2 : public Colleague {
public:
    ConcreteColleague2(Mediator* mediator, const string& name)
        : Colleague(mediator), name_(name) {}

    void send() override {
        cout << name_ << " is sending a message...\n";
        mediator_->broadcast(this);
    }

    void receive() override {
        cout << name_ << " received a message.\n";
    }

private:
    string name_;
};

// Client code
int main() {
    ConcreteMediator mediator;

    ConcreteColleague colleague1(&mediator, "Colleague 1");
    ConcreteColleague2 colleague2(&mediator, "Colleague 2");

    mediator.join(&colleague1);
    mediator.join(&colleague2);

    colleague1.send();
    colleague2.send();

    return 0;
}