#include <iostream>
#include <vector>
#include <algorithm>

// Observer interface: declares the update method
class Observer {
public:
    virtual ~Observer() {}
    virtual void update(int newState) = 0;
};

// Subject class: maintains a list of observers and notifies them of changes
class Subject {
private:
    std::vector<Observer*> observers;
    int state;
public:
    Subject() : state(0) {}

    // Register an observer
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    // Unregister an observer
    void detach(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    // Change the state and notify observers
    void setState(int newState) {
        state = newState;
        notify();
    }

    // Get the current state
    int getState() const {
        return state;
    }

    // Notify all registered observers of the state change
    void notify() {
        for (Observer* observer : observers) {
            observer->update(state);
        }
    }
};

// Concrete Observer A: reacts to subject's state changes
class ConcreteObserverA : public Observer {
public:
    void update(int newState) override {
        std::cout << "ConcreteObserverA: Subject's state changed to " << newState << std::endl;
    }
};

// Concrete Observer B: reacts to subject's state changes
class ConcreteObserverB : public Observer {
public:
    void update(int newState) override {
        std::cout << "ConcreteObserverB: Subject's state changed to " << newState << std::endl;
    }
};

int main() {
    Subject subject;

    ConcreteObserverA observerA;
    ConcreteObserverB observerB;

    // Register observers
    subject.attach(&observerA);
    subject.attach(&observerB);

    // Change state; both observers will be notified
    std::cout << "Setting state to 10." << std::endl;
    subject.setState(10);

    // Unregister observerA and change state again
    subject.detach(&observerA);
    std::cout << "\nSetting state to 20." << std::endl;
    subject.setState(20);

    return 0;
}
