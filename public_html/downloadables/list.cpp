#include <iostream>
#include <list>

using std::cout; using std::endl;
using std::list;

int main() {
    list<int> tod = {3, 4, 6, 2, 1, 10, 99999};
    for (auto i : tod) {
        cout << i << " ";
    }
    cout << endl;

    tod.reverse();
    for (auto i : tod) {
        cout << i << " ";
    }

    cout << endl;

    tod.sort();
    for (auto i : tod) {
        cout << i << " ";
    }

    cout << endl;

    tod.reverse();
    for (auto i : tod) {
        cout << i << " ";
    }
    cout << endl;
}