// composite design pattern

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::cin;

//component
class expression {
public:
    virtual int evaluate() = 0;
    virtual string print() = 0;
    virtual ~expression() {}
};

//leaf
class number : public expression {
public:
    number(int value) : value_(value) {}
    int evaluate() override {return value_;}
    string print() override {return std::to_string(value_);}
    ~number() override {}
private:
    int value_;
};

//composite
class add : public expression {
public:
    add(expression* left, expression* right) : left_(left), right_(right) {}
    int evaluate() override {return left_->evaluate() + right_->evaluate();}
    string print() override {return left_->print() + " + " + right_->print();}
    ~add() override {
        delete left_;
        delete right_;
    }
private:
    expression* left_;
    expression* right_;
};

class subtract : public expression {
public:
    subtract(expression* left, expression* right) : left_(left), right_(right) {}
    int evaluate() override {return left_->evaluate() - right_->evaluate();}
    string print() override {return left_->print() + " - " + right_->print();}
    ~subtract() override {
        delete left_;
        delete right_;
    }
private:
    expression* left_;
    expression* right_;
};

//client code
int main() {
    expression *const420 = new number(420);
    cout << const420->print() << " = " << const420->evaluate() << endl;

    expression *exp1 = new add(const420, new number(69));
    cout << exp1->print() << " = " << exp1->evaluate() << endl;

    expression *exp2 = new subtract(exp1, new number(10));
    cout << exp2->print() << " = " << exp2->evaluate() << endl;
}