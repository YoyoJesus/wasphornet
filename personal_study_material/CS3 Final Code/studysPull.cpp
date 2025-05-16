#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

// Abstract observer
class Observer {
public:
    Observer(string n) : name_(n), subj_(nullptr) {}
    virtual void notify() = 0;
    virtual void setSubject(class Subject*) = 0;

protected:
    class Subject* subj_;
    string name_;
};

// Abstract subject
class Subject {
public:
    Subject(string n) : payload_(n) {}

    virtual void registerObserver(Observer* o) {
        o->setSubject(this);
        views_.push_back(o);
    }

    virtual void deregister(Observer* o) {
        views_.erase(std::remove(views_.begin(), views_.end(), o), views_.end());
    }

    virtual void notifyOb() {
        for (auto o : views_) o->notify();
    }

    virtual string getPayload() const {
        return payload_;
    }

    virtual void changePayload(string n) {
        payload_ = n;
        notifyOb();
    }

protected:
    string payload_;
    vector<Observer*> views_;
};

// Concrete observer
class ConOB : public Observer {
public:
    ConOB(string n) : Observer(n) {}
    void notify() override {
        cout << name_ << " saw Change: " << subj_->getPayload() << endl;
    }
    void setSubject(Subject* s) {subj_ = s;}
};

// Concrete subject
class ConSub : public Subject {
public:
    ConSub(string n, string d) : Subject(d), name_(n) {}
private:
    string name_;
};

// Client code
int main() {
    Subject* subj = new ConSub("Subject1", "James");
    Observer* ob1 = new ConOB("OB1");
    Observer* ob2 = new ConOB("OB2");

    subj->registerObserver(ob1); // subj_ is set here
    subj->registerObserver(ob2); // subj_ is set here

    subj->changePayload("Smith");
}