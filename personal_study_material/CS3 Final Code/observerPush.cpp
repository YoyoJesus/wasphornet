// Observer Design Pattern
// Push model

#include <iostream>
#include <string>
#include <set>

using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::string;

// abstract observer
class Observer {
public:
    virtual void notify(const string &name) const = 0;
    virtual ~Observer() = default;
};

// abstract subject
class Subject {
public:
    void registerObserver(Observer *o) { views_.insert(o); }
    void deregisterObserver(Observer *o) { views_.erase(o); }
    void notifyObservers(const string &name) const {
        for (auto e : views_) e->notify(name);
    }
private:
    set<Observer *> views_;
};

// concrete observer
class ConcreteObserver : public Observer {
public:
    ConcreteObserver(const string &name) : name_(name) {}
    void notify(const string &name) const override {
        cout << "Observer " << name_ << " notified of change to subject: " << name << endl;
    }
private:
    string name_;
};

// concrete subject
class ConcreteSubject : public Subject {
public:
    ConcreteSubject(const string &name) : name_(name) {}
    void ChangeName(const string &name) {
        name_ = name;
        notifyObservers(name_); // Push updated data to observers
    }
    string getName() const { return name_; }
private:
    string name_;
};

// client code
int main() {
    ConcreteSubject subject("Initial Name");
    
    ConcreteObserver observer1("Observer 1");
    ConcreteObserver observer2("Observer 2");

    // Register observers
    subject.registerObserver(&observer1);
    subject.registerObserver(&observer2);

    // Notify observers of changes
    subject.ChangeName("New Name");
    
    // Deregister one observer and notify again
    subject.deregisterObserver(&observer1);
    subject.ChangeName("Another Name");

    return 0;
}