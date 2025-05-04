// Facade Design Pattern

#include <iostream>
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::vector;
using std::map;

// Subsystem classes
class SubsystemA {
public:
    void operationA() {
        cout << "SubsystemA: operationA" << endl;
    }
};

class SubsystemB {
public:
    void operationB() {
        cout << "SubsystemB: operationB" << endl;
    }
};

class SubsystemC {
public:
    void operationC() {
        cout << "SubsystemC: operationC" << endl;
    }
};

// Facade class
class Facade {
public:
    void operation1() {
        cout << "Facade: operation1:" << endl;
        subsystemA->operationA();
        subsystemB->operationB();
    }

    void operation2() {
        cout << "Facade: operation2:" << endl;
        subsystemB->operationB();
        subsystemC->operationC();
    }
private:
    SubsystemA* subsystemA;
    SubsystemB* subsystemB;
    SubsystemC* subsystemC;
};

// Client code
int main() {
    Facade facade;
    facade.operation1();
    facade.operation2();
}