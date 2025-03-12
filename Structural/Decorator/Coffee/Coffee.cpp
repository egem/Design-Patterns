#include <iostream>
#include <memory>
using namespace std;

// Component Interface
class Coffee {
public:
    virtual string getDescription() const = 0;
    virtual double getCost() const = 0;
    virtual ~Coffee() = default;
};

// Concrete Component: Basic Coffee
class BasicCoffee : public Coffee {
public:
    string getDescription() const override {
        return "Basic Coffee";
    }

    double getCost() const override {
        return 2.0; // Base price
    }
};

// Decorator Base Class
class CoffeeDecorator : public Coffee {
protected:
    shared_ptr<Coffee> coffee; // Wraps another Coffee object
public:
    CoffeeDecorator(shared_ptr<Coffee> coffee) : coffee(coffee) {}

    virtual string getDescription() const override {
        return coffee->getDescription(); // Default behavior
    }

    virtual double getCost() const override {
        return coffee->getCost(); // Default cost
    }
};

// Concrete Decorator 1: Milk
class Milk : public CoffeeDecorator {
public:
    Milk(shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee) {}

    string getDescription() const override {
        return coffee->getDescription() + ", Milk";
    }

    double getCost() const override {
        return coffee->getCost() + 0.5;
    }
};

// Concrete Decorator 2: Sugar
class Sugar : public CoffeeDecorator {
public:
    Sugar(shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee) {}

    string getDescription() const override {
        return coffee->getDescription() + ", Sugar";
    }

    double getCost() const override {
        return coffee->getCost() + 0.3;
    }
};

// Concrete Decorator 3: Whipped Cream
class WhippedCream : public CoffeeDecorator {
public:
    WhippedCream(shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee) {}

    string getDescription() const override {
        return coffee->getDescription() + ", Whipped Cream";
    }

    double getCost() const override {
        return coffee->getCost() + 0.7;
    }
};

int main() {
    shared_ptr<Coffee> coffee = make_shared<BasicCoffee>();
    cout << coffee->getDescription() << " -> Cost: $" << coffee->getCost() << endl;

    // Add Milk
    coffee = make_shared<Milk>(coffee);
    cout << coffee->getDescription() << " -> Cost: $" << coffee->getCost() << endl;

    // Add Sugar
    coffee = make_shared<Sugar>(coffee);
    cout << coffee->getDescription() << " -> Cost: $" << coffee->getCost() << endl;

    // Add Whipped Cream
    coffee = make_shared<WhippedCream>(coffee);
    cout << coffee->getDescription() << " -> Cost: $" << coffee->getCost() << endl;

    return 0;
}
