#include <iostream>
#include <memory>  // For smart pointers
using namespace std;

// Abstract Product: Vehicle
class Vehicle {
public:
    virtual void info() = 0;  // Pure virtual function
    virtual ~Vehicle() = default;
};

// Concrete Product: Car
class Car : public Vehicle {
public:
    void info() override {
        cout << "Car: A four-wheeled vehicle." << endl;
    }
};

// Concrete Product: Bike
class Bike : public Vehicle {
public:
    void info() override {
        cout << "Bike: A two-wheeled vehicle." << endl;
    }
};

// Factory Class
class VehicleFactory {
public:
    static unique_ptr<Vehicle> createVehicle(const string& type) {
        if (type == "car") {
            return make_unique<Car>();
        }
        else if (type == "bike") {
            return make_unique<Bike>();
        }
        else {
            return nullptr;  // Return null if type is unknown
        }
    }
};

int main() {
    // Create a Car using Factory
    unique_ptr<Vehicle> car = VehicleFactory::createVehicle("car");
    if (car) {
        car->info();
    }

    // Create a Bike using Factory
    unique_ptr<Vehicle> bike = VehicleFactory::createVehicle("bike");
    if (bike) {
        bike->info();
    }

    // Try an unknown type
    unique_ptr<Vehicle> unknown = VehicleFactory::createVehicle("truck");
    if (!unknown) {
        cout << "Unknown vehicle type!" << endl;
    }

    return 0;
}
