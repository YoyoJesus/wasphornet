// Abstract Factory
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::vector;

// Abstract Product
class Car {
public:
    Car(string model) : model_(model) {}
    virtual void drive() = 0;
protected:
    string model_;
};

// concrete product
class Ford : public Car {
public:
    Ford(string model) : Car(model) {}
    void drive() override {
        cout << "This is a Ford " << model_ << endl;
    }
};

class Chevy : public Car {
public:
    Chevy(string model) : Car(model) {}
    void drive() override {
        cout << "This is a Chevy " << model_ << endl; 
    }
};

class F1 : public Car {
public:
    F1(string model, string driver) : Car(model), driverName_(driver) {}
    void drive() override {
        cout << "This is a F1 " << model_ << " driven by " << driverName_ << endl;
    }
private:
    string driverName_;
};

// abstract factory
class CarFactory {
public:
    CarFactory(string factoryName) : factoryName_(factoryName) {}
    virtual Car* createCar() = 0;
private:
    string factoryName_;
};

// concrete factory
class FordFactory : public CarFactory {
public:
    FordFactory(string factoryName) : CarFactory(factoryName) {}
    Car* createCar() override {
        int index = rand() % models_.size();
        return new Ford(models_[index]);
    }
private:
    vector<string> models_ = {"Focus", "Mustang", "F-150", "Explorer", "Escape", "Fusion"};
};

class ChevyFactory : public CarFactory {
public:
    ChevyFactory(string factoryName) : CarFactory(factoryName) {}
    Car* createCar() override {
        int index = rand() % models_.size();
        return new Chevy(models_[index]);
    }
private:
    vector<string> models_ = {"Camero", "Chevelle", "Impala", "Malibu", "Silverado", "Equinox"};
};

class F1Factory : public CarFactory {
public:
    F1Factory(string factoryName) : CarFactory(factoryName) {}
    Car* createCar() override {
        int index = rand() % models_.size();
        int driverIndex = rand() % drivers_.size();
        return new F1(models_[index], drivers_[driverIndex]);
    }
private:
    vector<string> models_ = {"Ferrari", "Mercedes", "Red Bull", "McLaren", "Alpine", "Alpha Tauri"};
    vector<string> drivers_ = {"Hamilton", "Verstappen", "Leclerc", "Sainz", "Norris", "Alonso"};
};

//client
int main() {
    srand(time(nullptr));

    CarFactory* RougeFatory = new FordFactory("Rouge Plant");
    CarFactory* DetroitFactory = new ChevyFactory("Detroit Plant");
    CarFactory* F1 = new F1Factory("F1 Factory");

    vector<Car*> cars;
    cout << "Welcome to the Car Factory!" << endl;
    cout << "How many cars do you want to create? ";
    int numCars;
    cin >> numCars;
    cout << "Creating " << numCars << " cars..." << endl;
    for (int i = 0; i < numCars; ++i) {
        if (i % 2 == 0) 
            cars.push_back(RougeFatory->createCar());
        else if (i % 3 == 0) 
            cars.push_back(DetroitFactory->createCar());
        else 
            cars.push_back(F1->createCar());
    }

    for (auto car : cars) {
        car->drive();
    }
}