#include <iostream>
#include <vector>
#include <memory>

// Forward declarations for concrete elements
class ConcreteElementA;
class ConcreteElementB;

// Visitor interface: declares visit operations for each concrete element type.
class Visitor {
public:
    virtual ~Visitor() {}
    virtual void visitConcreteElementA(ConcreteElementA* element) = 0;
    virtual void visitConcreteElementB(ConcreteElementB* element) = 0;
};

// Element interface: declares an accept method that takes a visitor.
class Element {
public:
    virtual ~Element() {}
    virtual void accept(Visitor* visitor) = 0;
};

// ConcreteElementA: a concrete element that implements accept.
class ConcreteElementA : public Element {
public:
    void accept(Visitor* visitor) override {
        visitor->visitConcreteElementA(this);
    }

    // A specific operation for ConcreteElementA.
    void operationA() const {
        std::cout << "ConcreteElementA specific operation." << std::endl;
    }
};

// ConcreteElementB: another concrete element.
class ConcreteElementB : public Element {
public:
    void accept(Visitor* visitor) override {
        visitor->visitConcreteElementB(this);
    }

    // A specific operation for ConcreteElementB.
    void operationB() const {
        std::cout << "ConcreteElementB specific operation." << std::endl;
    }
};

// ConcreteVisitor: implements the Visitor interface to perform operations on elements.
class ConcreteVisitor : public Visitor {
public:
    void visitConcreteElementA(ConcreteElementA* element) override {
        std::cout << "Visitor processing ConcreteElementA:" << std::endl;
        element->operationA();
    }

    void visitConcreteElementB(ConcreteElementB* element) override {
        std::cout << "Visitor processing ConcreteElementB:" << std::endl;
        element->operationB();
    }
};

int main() {
    // Create a collection of elements
    std::vector<std::shared_ptr<Element>> elements;
    elements.push_back(std::make_shared<ConcreteElementA>());
    elements.push_back(std::make_shared<ConcreteElementB>());

    // Create a visitor
    ConcreteVisitor visitor;

    // Each element "accepts" the visitor, which processes the element.
    for (auto& element : elements) {
        element->accept(&visitor);
    }

    return 0;
}
