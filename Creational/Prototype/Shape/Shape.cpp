#include <iostream>
#include <memory>  // For smart pointers
using namespace std;

// Prototype (Base Class)
class Shape {
public:
    virtual void draw() = 0;               // Abstract method
    virtual unique_ptr<Shape> clone() = 0; // Prototype method
    virtual ~Shape() = default;            // Virtual destructor
};

// Concrete Prototype: Circle
class Circle : public Shape {
private:
    int radius;
public:
    Circle(int r) : radius(r) {}

    void draw() override {
        cout << "Drawing a Circle with radius: " << radius << endl;
    }

    unique_ptr<Shape> clone() override {
        return make_unique<Circle>(*this); // Cloning the object
    }
};

// Concrete Prototype: Rectangle
class Rectangle : public Shape {
private:
    int width, height;
public:
    Rectangle(int w, int h) : width(w), height(h) {}

    void draw() override {
        cout << "Drawing a Rectangle of " << width << "x" << height << endl;
    }

    unique_ptr<Shape> clone() override {
        return make_unique<Rectangle>(*this); // Cloning the object
    }
};

int main() {
    // Create original objects
    unique_ptr<Shape> circlePrototype = make_unique<Circle>(10);
    unique_ptr<Shape> rectanglePrototype = make_unique<Rectangle>(20, 30);

    // Clone the objects
    unique_ptr<Shape> clonedCircle = circlePrototype->clone();
    unique_ptr<Shape> clonedRectangle = rectanglePrototype->clone();

    // Draw the original and cloned objects
    cout << "Original Shapes:" << endl;
    circlePrototype->draw();
    rectanglePrototype->draw();

    cout << "Cloned Shapes:" << endl;
    clonedCircle->draw();
    clonedRectangle->draw();

    return 0;
}
