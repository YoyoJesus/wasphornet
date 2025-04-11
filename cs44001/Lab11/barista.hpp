//barista chain of command class
// to be used in Coffee Shack lab
// Austin Sternberg
// 4/11/2025

#include <string>
#include <iostream>
#include "drink.hpp" // Using Drink & getName() from drink.hpp

//observer imports
#include <list>
using std::list;

using std::cout; using std::endl; using std::cin;
using std::string;

// observer class
class Customer {
public:
    Customer(string name, Drink *drink = nullptr): name_(name), drink_(drink) {}
    void update(Drink *drink) {
        cout << "This is " << name_ << ", I got my coffee, thank you!" << endl;
    }
    string getName() const { return name_; } // Getter for name
    Drink* getDrink() const { return drink_; } // Getter for drink

    ~Customer() {
        delete drink_; // Clean up the drink object
    }
private:
    string name_;
    Drink *drink_; // Pointer to the drink object - helps to notify the customer
};

// abstract base class
class Barista { 
public:
    Barista(Barista *next = nullptr): nextBarista(next) {}
    virtual void handleOrder(Drink *order) {
        if (nextBarista != nullptr) {
            nextBarista->handleOrder(order);
        } else {
            cout << "No one can handle this order.";
        }
    }

    // Observer functions
    // Register a customer
    void attach(Customer *customer) {
        customers_.push_back(customer);
    }
    // Unregister a customer
    void detach(Customer *customer) {
        customers_.remove(customer);
    }
    // Notify the specific customer when their order is ready
    void notify(Customer *customer, Drink *drink) {
        if (customer != nullptr) {
            customer->update(drink);
        }
    }
    // Check if there are any customers
    bool hasCustomers() const {
        return !customers_.empty();
    }
    // Get the next customer in line
    Customer* getNextCustomer() {
        if (!customers_.empty()) {
            return customers_.front();
        }
        return nullptr;
    }

    // Destructor to clean up the list of customers
    ~Barista() {
        for (Customer* customer : customers_) {
            delete customer;
        }
        customers_.clear(); // Clear the list
    }
private:
    list<Customer*> customers_; // List of customers (observers)
    Barista *nextBarista;
};

class JuniorBarista : public Barista {
public:
    JuniorBarista(Barista *next = nullptr): Barista(next) {}
    void handleOrder(Drink *order) override {
        // JuniorBarista can only handle drinks with no added ingredients
        if (order->getName().find("honey") == string::npos &&
            order->getName().find("sugar") == string::npos &&
            order->getName().find("cream") == string::npos) 
        {
            cout << "It was prepared by a JuniorBarista.";
        } else {
            Barista::handleOrder(order);
        }
    }

    ~JuniorBarista() {}
};

class SeniorBarista : public Barista {
public:
    SeniorBarista(Barista *next = nullptr): Barista(next) {}
    void handleOrder(Drink *order) override {
        // SeniorBarista can handle all added ingredients except for honey
        if (order->getName().find("honey") == string::npos) {
            cout << "It was prepared by a SeniorBarista.";
        } else {
            Barista::handleOrder(order);
        }
    }

    ~SeniorBarista() {}
};

class Manager : public Barista {
public:
    Manager(Barista *next = nullptr): Barista(next) {}
    // Manager can handle any order
    void handleOrder(Drink *order) override {
        cout << "It was prepared by a Manager.";
        notify(nullptr, order); // Notify the attached customer when the order is ready
    }

    ~Manager() {}
};