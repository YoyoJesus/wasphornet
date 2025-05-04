// Observer Design Pattern
// Pull model

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
    Observer(class Subject *s);
    virtual void notify() const = 0;
};

// abstract subject
class Subject {
public:
    void registerObserver(Observer *o) { views_.insert(o); }
    void deregisterObserver(Observer *o) { views_.erase(o); }
    void notifyObservers() const{
        for (auto e : views_)
            e->notify();
    }
private:
    std::set<Observer *> views_;
};

Observer::Observer(Subject *s) {
    s->registerObserver(this);
}

// concrete observer
class ConcreteSubject;

class ConcreteObserver : public Observer {
public:
    ConcreteObserver(const string &, ConcreteSubject *);
    void notify() const override;
private:
    string name_;
    ConcreteSubject *subject_;
};

// concrete subject
class ConcreteSubject : public Subject {
public:
    ConcreteSubject(const string &name) : name_(name) {}
    void ChangeName(const string &name) { name_ = name; notifyObservers(); }
    string getName() const { return name_; }
private:
    string name_;
};

ConcreteObserver::ConcreteObserver(const string &name, ConcreteSubject *s) : Observer(s), name_(name), subject_(s) {}

void ConcreteObserver::notify() const {
    cout << "Observer " << name_ << " notified. Subject changed to: " << subject_->getName() << endl;
}

// client code
int main() {
    ConcreteSubject subj("Smith");

    ConcreteObserver obs1("Observer 1", &subj);
    ConcreteObserver obs2("Observer 2", &subj);

    subj.ChangeName("Jones");

    subj.deregisterObserver(&obs1);

    subj.ChangeName("Brown");
}