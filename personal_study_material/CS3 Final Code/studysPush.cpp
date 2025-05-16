#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

// abstract observer
class Observer {
public:
    Observer(string n) : name_(n) {}
    virtual void notify(string n) = 0;
protected:
    string name_;
};

// Abstract Subject
class Subject {
public:
    Subject(string n) : payload_(n) {}

    virtual void registerOB(Observer* o) {
        views_.push_back(o);
    }

    virtual void deregisterOB(Observer *o) {
        auto it = std::remove(views_.begin(), views_.end(), o);
        if (it != views_.end())
            views_.erase(it);
    }

    virtual void notifyOb(string n) {
        for (auto o : views_) o->notify(n);
    }

    virtual void change(string n) {
        payload_ = n;
        notifyOb(n);
    }
protected:
    string payload_;
    vector<Observer*> views_;
};

//Concrete ob
class ConOB : public Observer {
public:
    ConOB(string n) : Observer(n) {}
    void notify(string n) {
        cout << name_ << " saw Change: " << n << endl;
    }
};

// Concrete Sub
class ConSub : public Subject {
public:
    ConSub(string n, string d) : Subject(d), name_(n) {}
private:
    string name_;
};

int main() {
    Subject* subj = new ConSub("Sub1", "Smith");
    Observer* ob1 = new ConOB("OB1");
    Observer* ob2 = new ConOB("OB2");

    subj->registerOB(ob1);
    subj->registerOB(ob2);

    subj->change("James");
}