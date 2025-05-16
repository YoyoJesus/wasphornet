// Prototype Design Pattern
// Registry Design Pattern
// Type Covariance

#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::cin;
using std::map;
using std::string;

// abstract class
class Shape {
    public:
        Shape(int s) : size_(s) {}
        void resize(int s) {size_ = s;}
    
        virtual Shape* clone() const = 0;
        virtual void draw() const = 0;
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

// registry class
class ShapeRegistry {
public:
    static void setup(int size) {
        registry_ = {
            {"Circle", new Circle(size)},
            {"Square", new Square(size)}
        };
    }
    static Shape* create(string type) {
        return registry_[type]->clone();
    }
private:
    static map<string, Shape*> registry_;
};

map<string, Shape*> ShapeRegistry::registry_;

// client code
int main() {
    cout << "Shape Size: ";
    int size;
    cin >> size;
    ShapeRegistry::setup(size);
    
    Shape* circle = ShapeRegistry::create("Circle");
    Shape* square = ShapeRegistry::create("Square");
    
    circle->draw();
    square->draw();
    
    delete circle;
    delete square;
}