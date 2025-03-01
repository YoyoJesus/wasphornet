// picking the best quality lemons
// converting vectors to priority queue
// Mikhail Nesterenko modified by Austin Sternberg
// 2/17/2023

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::priority_queue;

struct Lemon {
    double quality;
    friend bool operator<(const Lemon& left, const Lemon& right) {
        return left.quality < right.quality;
    }
};

const int maxBoxSize = 30;
const int highestQuality = 10;

int main() {
    srand(time(nullptr));
    priority_queue <Lemon> box;


    // random quality assingment
    //for (auto& lemon : box)
    //    lemon.quality = static_cast<double>(rand()) / RAND_MAX * highestQuality;
    int randomBoxSize = rand() % maxBoxSize + 1;
    for (int i = 0; i < randomBoxSize; ++i) {
        Lemon lemon;
        lemon.quality = static_cast<double>(rand()) / RAND_MAX * highestQuality;
        box.push(lemon);
    }

    cout << "Here are the lemons (best first): ";

    // replace this code with priority queue
    //while (!box.empty()) {
    //    auto bestLemon = box.begin();
    //    for (auto lemon = bestLemon+1; lemon != box.end(); ++lemon)
    //        if (*bestLemon < *lemon) bestLemon = lemon;
    //    cout << bestLemon->quality << ", ";
    //    box.erase(bestLemon);
    //}
    while (!box.empty()) {
        cout << box.top().quality << ", ";
        box.pop();
    }
    cout << endl;
}

