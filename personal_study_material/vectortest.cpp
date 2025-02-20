#include <vector>
#include <iostream>

using std::vector;

int main() {
    vector<int> tod = {1, 2, 3};
    tod.reserve(50);
    tod.insert(tod.begin() + tod.capacity() - 4, 6);

    std::cout << tod.size() << std::endl;
    std::cout << tod.capacity() << std::endl;

    std::cout << std::endl;
    for (auto i : tod) {
        std::cout << i << std::endl;
    

    }
}