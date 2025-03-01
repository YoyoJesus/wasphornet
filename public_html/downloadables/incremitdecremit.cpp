# include <iostream>
#include <vector>

using std::cout; using std::endl;

class special_vector {
    public:
        special_vector(int size) : size_(size), data_(new int[size]) {}
        special_vector(const special_vector &other) : size_(other.size_), data_(new int[other.size_]) {
            for (int i = 0; i < size_; i++) {
                data_[i] = other.data_[i];
            }
        }
        special_vector(special_vector &&other) : size_(other.size_), data_(other.data_) {
            other.size_ = 0;
            other.data_ = nullptr;
        }
        ~special_vector() { delete[] data_; }
        int size() const { return size_; }
        int &operator[](int i) { return data_[i]; }
        int operator[](int i) const { return data_[i]; }

        special_vector& operator++ () {
            for (int i = 0; i < size_; i++) {
                data_[i]++;
            }
            return *this;
        }

        special_vector operator++ (int) {
            special_vector temp(*this);
            operator++();
            return temp;
        }

        special_vector& operator-- () {
            for (int i = 0; i < size_; i++) {
                data_[i]--;
            }
            return *this;
        }

        special_vector operator-- (int) {
            special_vector temp(*this);
            operator--();
            return temp;
        }
    private:
        int size_;
        int *data_;
};

int main() {
    special_vector v(5);
    for (int i = 0; i < v.size(); i++) {
        v[i] = i;
    }

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;

    special_vector v2 = v++;
    for (int i = 0; i < v2.size(); i++) {
        cout << v2[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;

    special_vector v3 = ++v;
    for (int i = 0; i < v3.size(); i++) {
        cout << v3[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;

    special_vector v4 = v--;
    for (int i = 0; i < v4.size(); i++) {
        cout << v4[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;

    special_vector v5 = --v;
    for (int i = 0; i < v5.size(); i++) {
        cout << v5[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}