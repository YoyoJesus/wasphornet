#include <iostream>
#include <string>

using std::cout;
using std::string; using std::to_string;

class State;

// process
class Process {
public:
    Process();

    // actions
    void create();
    void dispatch();
    void block();
    void unblock();
    void suspend();
    void exit();
    string report();

    // state change
    void changeState(State *state) { state_ = state;}
private:
    State* state_;
    int id_;
    static int num_;
};

// abstract state
class State {
public:
    virtual void dispatch(Process *) { }
    virtual void block(Process *) { }
    virtual void unblock(Process *) { }
    virtual void suspend(Process *) { }
    virtual void exit(Process *) { }
    virtual void create(Process *) { }

    virtual string report() = 0;

    void changeState(Process *p, State *s) {
        p->changeState(s);
    }
};

class NewState: public State {
public:
    static State* instance() {
        static State* onlyInstance = new NewState;
        return onlyInstance;
    }

    void create(Process *);

    string report() override { return "created"; }
private:
    NewState() { }
    NewState(const NewState &) = delete;
    NewState& operator=(const NewState &) = delete;
};

// concrete states
class Ready: public State {
public:
    static State* instance() {
        static State* onlyInstance = new Ready;
        return onlyInstance;
    }

    void dispatch(Process *);
    
    string report() override { return "READY"; }
private:
    Ready() { }
    Ready(const Ready &) = delete;
    Ready& operator=(const Ready &) = delete;
};

class Running: public State {
public:
    static State* instance() {
        static State* onlyInstance = new Running;
        return onlyInstance;
    }

    void block(Process *);
    void suspend(Process *);
    void exit(Process *);

    string report() override { return "RUNNING"; }
private:
    Running() { }
    Running(const Running &) = delete;
    Running& operator=(const Running &) = delete;
};

class Blocked: public State {
public:
    static State* instance()  {
        static State* onlyInstance = new Blocked;
        return onlyInstance;
    }

    void unblock(Process *);

    string report() override { return "BLOCKED"; }
private:
    Blocked() { }
    Blocked(const Blocked &) = delete;
    Blocked& operator=(const Blocked &) = delete;
};


class Exited: public State {
public:
    static State* instance()  {
        static State* onlyInstance = new Exited;
        return onlyInstance;
    }
    
    string report() override { return "exited"; }
private:
    Exited() { }
    Exited(const Exited &) = delete;
    Exited& operator=(const Exited &) = delete;
};


// Construction of Process & static variable
int Process::num_ = 0;
Process::Process() {
    state_ = NewState::instance();
    id_ = ++num_; // Assign id_ as num_ + 1 and increment num_
}

// state actions
void NewState::create(Process *p) {
    changeState(p, Ready::instance());
    cout << p->report();
}
void Ready::dispatch(Process *p) {
    changeState(p, Running::instance());
    cout << p->report();
}
void Running::block(Process *p) {
    changeState(p, Blocked::instance());
    cout << p->report();
}
void Running::suspend(Process *p) {
    changeState(p, Ready::instance());
    cout << p->report();
}
void Running::exit(Process *p) {
    changeState(p, Exited::instance());
    cout << p->report();
}
void Blocked::unblock(Process *p) {
    changeState(p, Ready::instance());
    cout << p->report();
}

// actions
void Process::create() { state_->create(this); }
void Process::dispatch() { state_->dispatch(this); }
void Process::block() { state_->block(this); }
void Process::unblock() { state_->unblock(this); }
void Process::suspend() { state_->suspend(this); }
void Process::exit() { state_->exit(this); }

string Process::report() {
    // check if state is running, blocked, or ready
    if (!(state_ == Exited::instance() || state_ == NewState::instance())) {
        return "PID " + to_string(id_) + " state: " + state_->report() + "\n";
    }
    // if state is exited or created
    else {
        return "PID " + to_string(id_) + ": " + state_->report() + "\n";
    }
}

