#include <iostream>
#include <memory>

// Strategy Interface: defines a common interface for all concrete strategies.
class Strategy {
public:
    virtual ~Strategy() {}
    virtual void execute() const = 0;
};

// Concrete Strategy A: Implements one version of the algorithm.
class ConcreteStrategyA : public Strategy {
public:
    void execute() const override {
        std::cout << "Executing Strategy A" << std::endl;
    }
};

// Concrete Strategy B: Implements another version of the algorithm.
class ConcreteStrategyB : public Strategy {
public:
    void execute() const override {
        std::cout << "Executing Strategy B" << std::endl;
    }
};

// Context: Maintains a reference to a Strategy object and delegates the work.
class Context {
private:
    std::shared_ptr<Strategy> strategy;
public:
    // Constructor with an optional strategy parameter.
    Context(const std::shared_ptr<Strategy>& strategy = nullptr) : strategy(strategy) {}

    // Set a different strategy at runtime.
    void setStrategy(const std::shared_ptr<Strategy>& strategy) {
        this->strategy = strategy;
    }

    // Execute the algorithm defined by the current strategy.
    void doSomething() const {
        if (strategy) {
            strategy->execute();
        } else {
            std::cout << "No strategy set" << std::endl;
        }
    }
};

int main() {
    // Create concrete strategy instances using smart pointers.
    std::shared_ptr<Strategy> strategyA = std::make_shared<ConcreteStrategyA>();
    std::shared_ptr<Strategy> strategyB = std::make_shared<ConcreteStrategyB>();

    // Create a context and set its strategy.
    Context context(strategyA);
    context.doSomething();  // Executes Strategy A

    // Change the strategy at runtime.
    context.setStrategy(strategyB);
    context.doSomething();  // Executes Strategy B

    return 0;
}
