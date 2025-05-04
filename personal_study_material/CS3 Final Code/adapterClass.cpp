//adapter design pattern
// class version
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

// adaptee
class Rectangle {
public:
    Rectangle(int width, int height, char c) : width_(width), height_(height), fillChar_(c) {}

    void draw() const {
        for (int i = 0; i < height_; ++i) {
            for (int j = 0; j < width_; ++j) {
                cout << fillChar_;
            }
            cout << endl;
        }
    }
private:
    int width_;
    int height_;
    char fillChar_;
};

// target interface
class Square {
public:
    virtual void draw() const = 0;
    virtual ~Square() {}
};

// adapter
class RectangleAdapter : public Square, private Rectangle {
public:
    RectangleAdapter(int size) : Rectangle(size, size, '&') {}
    void draw() const override {
        Rectangle::draw();
    }
};

// client code
int main() {
    cout << "Square Size: ";
    int size;
    cin >> size;
    Square *square = new RectangleAdapter(size);
    square->draw();
}