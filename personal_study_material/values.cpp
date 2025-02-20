#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cout; using std::endl; using std::move; using std::vector; using std::pair; using std::make_pair;
using std::string;

int foo(int a, int b) {
    return a + b;
}

int main() {
    int a, b;
    a=b=foo(3, 4)+7;

    vector<pair<int, string>> tod;
    pair<int, string> p(2, "Tuesday");
    tod.push_back(move(p));
    tod.push_back(make_pair(1, "Monday"));
    for (auto i : tod) {
        cout << i.first << " " << i.second << endl;
    }
    cout << "p: " << p.first << " " << p.second << endl;

    cout << tod[0].first << " " << tod[0].second << endl;

    cout << a << " " << b << endl;
}