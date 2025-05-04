// Chain of Responsibility Pattern

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

// abstract handler
class Handler {
public:
    Handler(Handler* suc=nullptr) : successor_(suc) {}
    virtual void handleRequest(int amount) {
        if (successor_ != nullptr)
            successor_->handleRequest(amount);
        else
            cout << "No handler available for amount: " << amount << endl;
    }
private:
    Handler *successor_;
};

// concrete handler
class ConcreteHandlerA : public Handler {
public:
    ConcreteHandlerA(Handler* suc=nullptr) : Handler(suc) {}
    void handleRequest(int amount) override {
        if (amount < 500)
            cout << "Handler A handled request for amount: " << amount << endl;
        else
            Handler::handleRequest(amount);
    }
};

class ConcreteHandlerB : public Handler {
public:
    ConcreteHandlerB(Handler* suc=nullptr) : Handler(suc) {}
    void handleRequest(int amount) override {
        if (amount < 1000)
            cout << "Handler B handled request for amount: " << amount << endl;
        else
            Handler::handleRequest(amount);
    }
};

class ConcreteHandlerC : public Handler {
public:
    ConcreteHandlerC(Handler* suc=nullptr) : Handler(suc) {}
    void handleRequest(int amount) override {
        if (amount < 5000)
            cout << "Handler C handled request for amount: " << amount << endl;
        else
            Handler::handleRequest(amount);
    }
};

// client code
int main() {
    Handler* chain = new ConcreteHandlerA(new ConcreteHandlerB(new ConcreteHandlerC()));

    int amount = 0;
    do {
        cout << "Enter amount to be handled (0 to exit): ";
        cin >> amount;
        if (amount != 0)
            chain->handleRequest(amount);
    } while (amount != 0);
}