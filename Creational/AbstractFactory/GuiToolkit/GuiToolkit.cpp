#include <iostream>
using namespace std;

// Abstract Product - Button
class Button {
public:
    virtual void render() const = 0;
    virtual void onClick() const = 0;
    virtual ~Button() = default;
};

// Abstract Product - Checkbox
class Checkbox {
public:
    virtual void render() const = 0;
    virtual void onClick() const = 0;
    virtual ~Checkbox() = default;
};

// Concrete Product - Windows Button
class WindowsButton : public Button {
public:
    void render() const override {
        cout << "Rendering Windows Button" << endl;
    }

    void onClick() const override {
        cout << "Windows Button clicked!" << endl;
    }
};

// Concrete Product - Windows Checkbox
class WindowsCheckbox : public Checkbox {
public:
    void render() const override {
        cout << "Rendering Windows Checkbox" << endl;
    }

    void onClick() const override {
        cout << "Windows Checkbox clicked!" << endl;
    }
};

// Concrete Product - macOS Button
class MacOSButton : public Button {
public:
    void render() const override {
        cout << "Rendering macOS Button" << endl;
    }

    void onClick() const override {
        cout << "macOS Button clicked!" << endl;
    }
};

// Concrete Product - macOS Checkbox
class MacOSCheckbox : public Checkbox {
public:
    void render() const override {
        cout << "Rendering macOS Checkbox" << endl;
    }

    void onClick() const override {
        cout << "macOS Checkbox clicked!" << endl;
    }
};

// Abstract Factory - GUI Factory
class GUIFactory {
public:
    virtual shared_ptr<Button> createButton() const = 0;
    virtual shared_ptr<Checkbox> createCheckbox() const = 0;
    virtual ~GUIFactory() = default;
};

// Concrete Factory - Windows Factory
class WindowsFactory : public GUIFactory {
public:
    shared_ptr<Button> createButton() const override {
        return make_shared<WindowsButton>();
    }

    shared_ptr<Checkbox> createCheckbox() const override {
        return make_shared<WindowsCheckbox>();
    }
};

// Concrete Factory - macOS Factory
class MacOSFactory : public GUIFactory {
public:
    shared_ptr<Button> createButton() const override {
        return make_shared<MacOSButton>();
    }

    shared_ptr<Checkbox> createCheckbox() const override {
        return make_shared<MacOSCheckbox>();
    }
};

int main() {
    // Client code
    unique_ptr<GUIFactory> factory;

    // Simulating different OS environments
    string platform = "Windows";  // Can be "Windows" or "macOS"

    if (platform == "Windows") {
        factory = make_unique<WindowsFactory>();
    } else if (platform == "macOS") {
        factory = make_unique<MacOSFactory>();
    }

    shared_ptr<Button> button = factory->createButton();
    shared_ptr<Checkbox> checkbox = factory->createCheckbox();

    button->render();
    button->onClick();

    checkbox->render();
    checkbox->onClick();

    return 0;
}
