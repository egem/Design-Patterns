#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Product: Meal (a collection of items)
class Meal {
private:
    vector<string> items;

public:
    void addItem(const string& item) {
        items.push_back(item);
    }

    void showItems() const {
        cout << "Meal contains: ";
        for (const auto& item : items) {
            cout << item << " ";
        }
        cout << endl;
    }

    double getCost() const {
        double cost = 0;
        for (const auto& item : items) {
            if (item == "Burger") cost += 5.0;
            else if (item == "Fries") cost += 2.0;
            else if (item == "Coke") cost += 1.5;
            else if (item == "Salad") cost += 3.0;
        }
        return cost;
    }
};

// Abstract Builder: Builder for Meal
class MealBuilder {
public:
    virtual void buildBurger() = 0;
    virtual void buildFries() = 0;
    virtual void buildDrink() = 0;
    virtual void buildSalad() = 0;

    virtual shared_ptr<Meal> getMeal() = 0;
    virtual ~MealBuilder() = default;
};

// Concrete Builder: Veg Meal
class VegMealBuilder : public MealBuilder {
private:
    shared_ptr<Meal> meal;

public:
    VegMealBuilder() { meal = make_shared<Meal>(); }

    void buildBurger() override {
        meal->addItem("Veg Burger");
    }

    void buildFries() override {
        meal->addItem("Fries");
    }

    void buildDrink() override {
        meal->addItem("Coke");
    }

    void buildSalad() override {
        meal->addItem("Salad");
    }

    shared_ptr<Meal> getMeal() override {
        return meal;
    }

    ~VegMealBuilder() {}
};

// Concrete Builder: Non-Veg Meal
class NonVegMealBuilder : public MealBuilder {
private:
    shared_ptr<Meal> meal;

public:
    NonVegMealBuilder() { meal = make_shared<Meal>(); }

    void buildBurger() override {
        meal->addItem("Chicken Burger");
    }

    void buildFries() override {
        meal->addItem("Fries");
    }

    void buildDrink() override {
        meal->addItem("Coke");
    }

    void buildSalad() override {
        meal->addItem("Salad");
    }

    shared_ptr<Meal> getMeal() override {
        return meal;
    }

    ~NonVegMealBuilder() {}
};

// Director: Responsible for constructing the Meal using a specific builder
class MealDirector {
private:
    shared_ptr<MealBuilder> builder;

public:
    MealDirector(shared_ptr<MealBuilder> builder) : builder(builder) {}

    shared_ptr<Meal> createMeal() {
        builder->buildBurger();
        builder->buildFries();
        builder->buildDrink();
        builder->buildSalad();
        return builder->getMeal();
    }
};

int main() {
    // Create a Veg Meal using the builder pattern
    shared_ptr<MealBuilder> vegMealBuilder = make_shared<VegMealBuilder>();
    MealDirector vegMealDirector(vegMealBuilder);
    shared_ptr<Meal> vegMeal = vegMealDirector.createMeal();

    vegMeal->showItems();
    cout << "Total Cost: $" << vegMeal->getCost() << endl;

    // Create a Non-Veg Meal using the builder pattern
    shared_ptr<MealBuilder> nonVegMealBuilder = make_shared<NonVegMealBuilder>();
    MealDirector nonVegMealDirector(nonVegMealBuilder);
    shared_ptr<Meal> nonVegMeal = nonVegMealDirector.createMeal();

    nonVegMeal->showItems();
    cout << "Total Cost: $" << nonVegMeal->getCost() << endl;

    return 0;
}
