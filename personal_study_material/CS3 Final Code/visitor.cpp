// visitor design pattern

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::cin;

// abstract element
class Shape {
public:
    virtual void accept(class ShapeVisitor* visitor) = 0;
};

// abstract visitor
class ShapeVisitor {
public:
    virtual void visit(class Circle* circle) = 0;
    virtual void visit(class Square* square) = 0;
};

// concrete element
class Circle : public Shape {
public:
    void accept(ShapeVisitor* visitor) override {
        visitor->visit(this);
    }

    Circle(int r) : radius(r) {}
    int getRadius() const { return radius; }
    void setRadius(int r) { radius = r; }
private:
    int radius;
};

class Square : public Shape {
public:
    void accept(ShapeVisitor* visitor) override {
        visitor->visit(this);
    }

    Square(int s) : side(s) {}
    int getSide() const { return side; }
    void setSide(int s) { side = s; }
private:
    int side;
};

// concrete visitor
class ShapePainter : public ShapeVisitor {
public:
    void visit(Circle* circle) override {
        cout << "Painting Circle with radius: " << circle->getRadius() << endl;
    }

    void visit(Square* square) override {
        cout << "Painting Square with side: " << square->getSide() << endl;
    }
};

class AreaCalculator : public ShapeVisitor {
public:
    void visit(Circle* circle) override {
        double area = 3.14 * circle->getRadius() * circle->getRadius();
        cout << "Area of Circle: " << area << endl;
    }

    void visit(Square* square) override {
        int area = square->getSide() * square->getSide();
        cout << "Area of Square: " << area << endl;
    }
};

// client code
int main() {
    Circle circle(5);
    Square square(4);

    ShapePainter painter;
    AreaCalculator areaCalculator;

    circle.accept(&painter);
    square.accept(&painter);

    circle.accept(&areaCalculator);
    square.accept(&areaCalculator);

    return 0;
}