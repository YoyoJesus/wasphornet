// Memento Design Pattern

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using std::vector;
using std::cout;
using std::endl;
using std::cin;

// Originator class
class storage {
public:
    storage(int x) {
        std::generate_n(back_inserter(data_), x, []() { return rand() % 100; });
    }
    void show() {
        cout << "Current data: ";
        for (int i : data_) {
            cout << i << " ";
        }
        cout << endl;
    }
    void add(int x) {
        data_.push_back(x);
        cout << "Added " << x << endl;
    }
    void remove(int x) {
        auto it = std::remove(data_.begin(), data_.end(), x);
        if (it != data_.end()) {
            data_.erase(it);
            cout << "Removed " << x << endl;
        } else {
            cout << x << " not found" << endl;
        }
    }

    class Memnto *checkpoint() const;
    void rollback(const class Memnto*);
private:
    vector<int> data_;
};

// Memento class
class Memnto {
public:
    Memnto(const storage& data) : data_(data) {}
    const storage& getData() const { return data_; }
private:
    const storage data_;
};

Memnto *storage::checkpoint() const { cout << "Checkpoint Created" << endl; return new Memnto(*this); }

void storage::rollback(const Memnto *memento) {cout << "Data Rollback" << endl; *this = memento->getData();}

// Caretaker & Client
int main() {
    srand(time(nullptr));

    storage s(5);
    s.show();
    s.add(42);
    s.show();
    Memnto *memento = s.checkpoint();
    s.remove(42);
    s.show();
    s.rollback(memento);
    s.show();
}