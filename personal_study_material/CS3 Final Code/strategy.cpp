// strategy design pattern

#include <iostream>

using std::cout;
using std::endl;
using std::cin;

// abstract strategy class
class Strategy {
public:
    virtual void algorithm() = 0; // pure virtual function
};

// concrete strategy class
class ConcreteStrategyA : public Strategy {
public:
    void algorithm() override {
        cout << "ConcreteStrategyA algorithm" << endl;
    }
};

class ConcreteStrategyB : public Strategy {
public:
    void algorithm() override {
        cout << "ConcreteStrategyB algorithm" << endl;
    }
};

// context class
class Context {
public:
    Context(Strategy* strategy) : strategy_(strategy) {} // constructor
    void setStrategy(Strategy* strat) { strategy_ = strat; } // set strategy
    void executeAlgorithm() { strategy_->algorithm(); } // execute algorithm
private:
    Strategy* strategy_; // pointer to strategy object
};

// client code
int main() {
    ConcreteStrategyA strategyA;
    ConcreteStrategyB strategyB;

    Context context(&strategyA); // create context with strategy A
    context.executeAlgorithm(); // execute algorithm of strategy A

    context.setStrategy(&strategyB); // change to strategy B
    context.executeAlgorithm(); // execute algorithm of strategy B
}