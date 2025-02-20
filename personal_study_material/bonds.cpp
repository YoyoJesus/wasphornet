#include <iostream>
#include <map>
#include <string>

using std::cout; using std::endl;
using std::map; using std::string;

int main() {
    map<int, string> bonds = {{1, "James"}, {5, "Jane"}, {10, "John"}};

    cout << "The bounds are: " << endl;
    auto ret = bonds.upper_bound(1);

    auto ret2 = bonds.lower_bound(1);

    //print out the bonds
    cout << "Upper bound: " << ret->first << " " << ret->second << endl;
    cout << "Lower bound: " << ret2->first << " " << ret2->second << endl;


}