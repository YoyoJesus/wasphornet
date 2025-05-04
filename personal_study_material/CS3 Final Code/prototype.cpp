// prototype design pattern
// Demos type covariance

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::cin;

// abstract class
class Shape {
public:
    Shape(int s) : size_(s) {}
    void resize(int s) {size_ = s;}

    virtual Shape* clone() const = 0;
    virtual void draw() const = 0;
    virtual ~Shape() {}
protected:
    int size_;
};

// concrete class
class Circle : public Shape { 
public:
    Circle(int s) : Shape(s) {}
    Circle* clone() const override { return new Circle(*this); }
    void draw() const override { cout << "Drawing Circle of size " << size_ << endl; }
};

class Square : public Shape {
public:
    Square(int s) : Shape(s) {}
    Square* clone() const override { return new Square(*this); }
    void draw() const override { cout << "Drawing Square of size " << size_ << endl; }
};

// client code
int main() {
    vector<Shape*> shapes;
    shapes.push_back(new Circle(5));
    shapes.push_back(new Square(10));

    for (const auto& shape : shapes) {
        shape->draw();
    }

    // cloning
    vector<Shape*> clones;
    for (const auto& shape : shapes) {
        clones.push_back(shape->clone());
    }

    cout << "Cloned Shapes:" << endl;
    for (const auto& clone : clones) {
        clone->draw();
    }
}
