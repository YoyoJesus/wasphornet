#include "../drink.hpp"
#include <iostream>
#include <string>

using std::cout; using std::endl; using std::cin;
using std::string;

int main () {
    char choice;

    cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? ";
    cin >> choice;
    
    Drink *coffee;
    switch (choice) {
        case 'l':
            coffee = new Drink(DrinkType::large);
            break;
        case 'm':
            coffee = new Drink(DrinkType::medium);
            break;
        case 's':
            coffee = new Drink(DrinkType::small);
            break;
        default:
            cout << "Invalid choice, try again!" << endl;
    }
    cout << endl;

    while (choice != 'd') {
        cout << "Would you like to add [s]ugar, [h]oney, [c]ream, or [d]one? ";
        cin >> choice;

        switch (choice) {
            case 's':
                coffee = new Sugar(coffee);
                break;
            case 'h':
                coffee = new Honey(coffee);
                break;
            case 'c':
                coffee = new Cream(coffee);
                break;
            case 'd':
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
        cout << endl;
    }
    cout << endl;

    cout << "Can I get your name? ";
    string name;
    cin >> name;
    cout << endl;
    cout << name + ", your " + coffee->getName() + " is ready! It wiil be $" << coffee->getPrice() << " please." << endl;

    // Clean up
    delete coffee;
}