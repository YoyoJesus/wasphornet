// Show how find_first_off works

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using std::cout; using std::endl;
using std::vector;

int main() {
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> v2 = {3,1};
    auto it = find_first_of(v.begin(), v.end(), v2.begin(), v2.end());
    cout << *it << endl;
    
    // so that vectors are allocated on the stack - why we didn't know this, don't know
    cout << distance(v.begin(), v2.begin()) << endl;

    // fill a vector with numbers 1-100
    vector<int> v3;
    generate_n(back_inserter(v3), 100, []() { static int i = 0; return ++i; });

    auto it2 = v3.rbegin();
    while(*it2 != 60) {
        cout << *it2 << " ";
        advance(it2, 1);
    }
    cout << endl;

    auto itBase = it2.base();
    cout << *itBase << endl;
    advance(itBase, 20);
    cout << *itBase << endl;
}