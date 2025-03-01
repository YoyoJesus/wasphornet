#include <iostream>
#include <map>
#include <string>

using std::cout; using std::endl;
using std::string; using std::map;

int main() {
    map<int, string> tod;

    const map<int, string> tod2 = {
        {1, "Monday"},
        {2, "Tuesday"},
        {3, "Wednesday"},
        {4, "Thursday"},
        {5, "Friday"},
        {6, "Saturday"},
        {7, "Sunday"}
    };

    while (true) {
        int num;
        string name;

        cout << "Enter a number and a name: ";
        std::cin >> num >> name;

        auto ret = tod.insert(std::make_pair(num, name));

        if (ret.second) {
            cout << "Inserted " << num << " " << name << endl;
        } else {
            cout << "Failed to insert " << num << " " << name << endl;
            break;
        }
    }

    //print out the map
    for (auto i : tod) {
        cout << i.first << " " << i.second << endl;
    }
}