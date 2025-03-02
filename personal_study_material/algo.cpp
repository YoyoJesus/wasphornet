#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <string>

using std::cout; using std::cin; using std::endl;
using std::vector; using std::for_each;

int main() {
    vector<int> v;

    // push 1 - 100 into the vector
    for (int i = 1; i <= 15; i++) {
        v.push_back(i);
    }

    // fizzbuzz
    for_each(v.begin(), v.end(), [](int element) {
        cout << element << " ";
        if (element % 3 == 0) cout << "Fizz";
        if (element % 5 == 0) cout << "Buzz";
        cout << endl;
    });

    //accumalate sum
    int sum = accumulate(v.begin(), v.end(), 0);
    cout << "Sum: " << sum << endl;

    //accumalate product
    int product = accumulate(v.begin(), v.end(), 1, [](int a, int b) {
        return a * b;
    });
    cout << "Product: " << product << endl;

    //generate random numbers for vector
    srand(time(0));
    generate (v.begin(), v.end(), []() {
        return rand() % 100;
    });
    for_each(v.begin(), v.end(), [](int element) {
        cout << element << " ";
    });
    cout << endl;

    //check if any elements equal 55
    int num = 55;
    int count = count_if(v.begin(), v.end(), [&num](int element) {
        return element == num;
    });
    cout << "Number of elements equal to " << num << ": " << count << endl;

    //move all elemnts larger than 50 to a new vector
    vector<int> v2;
    auto it = remove_copy_if(v.begin(), v.end(), back_inserter(v2), [](int element) {
        return element <= 50;
    });

    for (auto element : v) {
        cout << element << " ";
    }
    cout << endl;
    for (auto element : v2) {
        cout << element << " ";
    }
    cout << endl;
