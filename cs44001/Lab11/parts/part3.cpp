#include "../barista.hpp" // drink.hpp is included in barista.hpp
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout; using std::endl; using std::cin;

int main() {
    srand(time(0));
    Barista *baristaPointer = new JuniorBarista(new SeniorBarista(new Manager()));
    int totalOrders = 0;

    while (totalOrders < 3 || baristaPointer->hasCustomers()) {
        if (totalOrders < 3) {
            // Take a new order
            Drink *coffee = nullptr;
            static char choice;

            cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? ";
            cin >> choice;

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
                    continue; // Skip to the next iteration
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
            
            static string name;
            cout << "Can I get your name? ";
            cin >> name;
            Customer *customer = new Customer(name, coffee);
            baristaPointer->attach(customer);
            cout << endl;
            cout << "Please wait " + name + "." << endl;

            totalOrders++;
        } else if (baristaPointer->hasCustomers()) {
            // Make a drink for an existing customer
            Customer *cust = baristaPointer->getNextCustomer();

            cout << cust->getName() + ", your " + cust->getDrink()->getName() + " is ready! ";
            baristaPointer->handleOrder(cust->getDrink());
            cout << " It will be $" << cust->getDrink()->getPrice() << " please." << endl;
            baristaPointer->notify(cust->getDrink()); // Notify the specific customer
            baristaPointer->detach(cust); // Detach the customer after notifying

            delete cust; // Clean up the customer object
        }
        cout << endl;
    }
    cout << endl;
    cout << "All orders have been completed. Thank you for visiting Coffee Shack!" << endl;

    // Clean up
    delete baristaPointer; 
}