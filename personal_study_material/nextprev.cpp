#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <deque>
#include <string>

using std::cout; using std::cin; using std::endl;
using std::vector; using std::deque;
using std::string;

int main() {
    /*
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> v2 = {10, 11, 12, 13, 14, 15, 16, 17, 18};

    vector<int> v3(v.size());

    // transform
    transform(v.begin(), v.end(), v2.begin(), v3.begin(), [](int a, int b) {
        return a + b;
    });

    for_each(v3.begin(), v3.end(), [](int element) {
        cout << element << " ";
    });
    cout << endl;

    // transform on v1 to v1
    transform(v.begin(), v.end(), v.begin(), [](int a) {
        return a * 2;
    });

    // v1
    cout << "v1: ";
    for_each(v.begin(), v.end(), [](int element) {
        cout << element << " ";
    });
    cout << endl;

    // v2
    cout << "v2: ";
    for_each(v2.begin(), v2.end(), [](int element) {
        cout << element << " ";
    });
    cout << endl;

    // insert iterator
    copy(v.begin(), v.end(), inserter(v3, v3.begin()));

    // back & front inserter iterator
    deque <int> d;
    copy(v.begin(), v.end(), back_inserter(d));
    copy(v.begin(), v.end(), front_inserter(d));


    vector<int> v4;
    generate_n(back_inserter(v4), 2, [v](int i){return v[i];});
*/

    /*
    // hello
    // hi
    string s = "123";
    string ss = "1234";
    auto it = lexicographical_compare(s.begin(), s.end(), ss.begin(), ss.end());
    if (it) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    */

    // 1 2 3 4 5 6 7 8 9
    // remove 2 =< x < 5
    // 1 5 6 7 8 9 7 8 9
    //             ^

    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> v2 = {10, 11, 12, 13, 14, 15, 16, 17, 18};

    //copy(v.begin(), v.end(), v2.begin());
    //copy_if(v.begin(), v.end(), v2.begin(), [](int x) { return x > 5; });
    //remove_copy(v.begin(), v.end(), v2.begin(), 2);
    auto it = remove_copy_if(v.begin(), v.end(), v2.begin(), [](int x) { return x > 5; });
    v2.erase(it, v2.end());

    for(auto e : v) {
        cout << e << " ";
    }
    cout << endl;   
    for(auto e : v2) {
        cout << e << " ";
    }
}