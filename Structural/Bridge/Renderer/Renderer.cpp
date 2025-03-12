#include <iostream>
using namespace std;

// Implementor interface (Bridge)
class Renderer {
public:
    virtual void renderCircle(float x, float y, float radius) = 0;
    virtual void renderRectangle(float x, float y, float width, float height) = 0;
    virtual ~Renderer() = default;
};

// Concrete Implementor 1: OpenGL Renderer
class OpenGLRenderer : public Renderer {
public:
    void renderCircle(float x, float y, float radius) override {
        cout << "OpenGL: Drawing Circle at (" << x << "," << y << ") with radius " << radius << endl;
    }

    void renderRectangle(float x, float y, float width, float height) override {
        cout << "OpenGL: Drawing Rectangle at (" << x << "," << y << ") with width " << width << " and height " << height << endl;
    }
};

// Concrete Implementor 2: DirectX Renderer
class DirectXRenderer : public Renderer {
public:
    void renderCircle(float x, float y, float radius) override {
        cout << "DirectX: Drawing Circle at (" << x << "," << y << ") with radius " << radius << endl;
    }

    void renderRectangle(float x, float y, float width, float height) override {
        cout << "DirectX: Drawing Rectangle at (" << x << "," << y << ") with width " << width << " and height " << height << endl;
    }
};

// Abstraction (Shape)
class Shape {
protected:
    shared_ptr<Renderer> renderer; // Bridge to Implementation
public:
    Shape(shared_ptr<Renderer> r) : renderer(r) {}
    virtual void draw() = 0; // Pure virtual function
    virtual ~Shape() = default;
};

// Refined Abstraction 1: Circle
class Circle : public Shape {
private:
    float x, y, radius;
public:
    Circle(shared_ptr<Renderer> r, float x, float y, float radius)
        : Shape(r), x(x), y(y), radius(radius) {}

    void draw() override {
        renderer->renderCircle(x, y, radius);
    }
};

// Refined Abstraction 2: Rectangle
class Rectangle : public Shape {
private:
    float x, y, width, height;
public:
    Rectangle(shared_ptr<Renderer> r, float x, float y, float width, float height)
        : Shape(r), x(x), y(y), width(width), height(height) {}

    void draw() override {
        renderer->renderRectangle(x, y, width, height);
    }
};

int main() {
    shared_ptr<Renderer> opengl = make_shared<OpenGLRenderer>();
    shared_ptr<Renderer> directx = make_shared<DirectXRenderer>();

    unique_ptr<Shape> circle1 = make_unique<Circle>(opengl, 5, 5, 10);
    unique_ptr<Shape> rect1 = make_unique<Rectangle>(directx, 10, 10, 20, 30);

    circle1->draw();
    rect1->draw();

    return 0;
}

