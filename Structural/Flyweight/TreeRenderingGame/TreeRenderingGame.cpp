#include <iostream>
#include <unordered_map>
using namespace std;

// Flyweight: Shared tree data (intrinsic state)
class TreeType {
private:
    string name;
    string color;
    string texture;

public:
    TreeType(string name, string color, string texture)
        : name(name), color(color), texture(texture) {}

    void display(int x, int y) const {
        cout << "Tree: " << name << ", Color: " << color
             << ", Texture: " << texture
             << " at (" << x << ", " << y << ")" << endl;
    }
};

// Flyweight Factory: Manages shared tree types
class TreeFactory {
private:
    static unordered_map<string, shared_ptr<TreeType>> treeTypes;

public:
    static shared_ptr<TreeType> getTreeType(string name, string color, string texture) {
        string key = name + "_" + color + "_" + texture;

        if (treeTypes.find(key) == treeTypes.end()) {
            treeTypes[key] = make_shared<TreeType>(name, color, texture);
        }

        return treeTypes[key]; // Return shared instance
    }
};

// Definition of static member
unordered_map<string, shared_ptr<TreeType>> TreeFactory::treeTypes;

// Context: Stores unique position for each tree
class Tree {
private:
    int x, y; // Unique state (extrinsic)
    shared_ptr<TreeType> type;

public:
    Tree(int x, int y, shared_ptr<TreeType> type) : x(x), y(y), type(type) {}

    void display() const {
        type->display(x, y);
    }
};

int main() {
    cout << "=== Flyweight Pattern: Tree Rendering ===" << endl;

    shared_ptr<TreeType> oakType = TreeFactory::getTreeType("Oak", "Green", "Rough");
    shared_ptr<TreeType> pineType = TreeFactory::getTreeType("Pine", "Dark Green", "Smooth");

    Tree tree1(10, 20, oakType);
    Tree tree2(30, 40, oakType);
    Tree tree3(50, 60, pineType);

    tree1.display();
    tree2.display();
    tree3.display();

    return 0;
}

