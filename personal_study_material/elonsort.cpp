// This is essentially a simulation of a government plan.
// This is a simple program that uses a list to simulate the employees and then uses the same list to simulate the firing and rehiring of the employees.
// The program uses the random number generator to simulate the firing and rehiring of the employees.
// Thanks for the idea.

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <list>

using std::cout; using std::endl; using std::list;

const int EMPLOYEES = 50;

int main() {
    srand(time(0));

    //populate vector with random numbers
    list<int> GovEmployees;
    for (int i = 0; i < EMPLOYEES; ++i) {
        GovEmployees.push_back(rand() % 99 + 1);
    }

    //print out the vector
    cout << "Gov Employees: " << endl;
    for (const auto& i : GovEmployees) {
        cout << i << " ";
    }
    cout << endl;
    
    // use custom sort to sort the vector
    list<int> FiredGovEmployees;
    //int randomInt = rand() % 99 + 1;
    int randomInt = 5; // for testing purposes
    cout << "Random Int: " << randomInt << endl;

    // Custom sort
    while (randomInt > 0) {

        // Fire half of the employees at random
        for (int i = 0; i < EMPLOYEES/2; ++i) {
            FiredGovEmployees.push_back(GovEmployees.front());
            GovEmployees.pop_front();
        }
        
        cout << "Fired Employees" << endl;

        // Rehire the employees
        cout << "We made a mistake, rehire the employees" << endl;
        while (!FiredGovEmployees.empty()) {
            GovEmployees.push_back(FiredGovEmployees.front());
            FiredGovEmployees.pop_front();
        }

        --randomInt;
    }

    cout << "Sorted Gov Employees: " << endl;
    for (const auto& i : GovEmployees) {
        cout << i << " ";
    }
    cout << endl;

}