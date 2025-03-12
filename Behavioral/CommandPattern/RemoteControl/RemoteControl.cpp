#include <iostream>
#include <memory>

// Command interface: declares a method for executing a command.
class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

// Receiver: the class that performs the actual work.
class Light {
public:
    void on() {
        std::cout << "The light is on." << std::endl;
    }
    void off() {
        std::cout << "The light is off." << std::endl;
    }
};

// Concrete Command: turns the light on.
class LightOnCommand : public Command {
private:
    std::shared_ptr<Light> light;
public:
    LightOnCommand(const std::shared_ptr<Light>& light) : light(light) {}
    void execute() override {
        light->on();
    }
};

// Concrete Command: turns the light off.
class LightOffCommand : public Command {
private:
    std::shared_ptr<Light> light;
public:
    LightOffCommand(const std::shared_ptr<Light>& light) : light(light) {}
    void execute() override {
        light->off();
    }
};

// Invoker: holds and executes a command.
class RemoteControl {
private:
    std::shared_ptr<Command> command;
public:
    void setCommand(const std::shared_ptr<Command>& cmd) {
        command = cmd;
    }
    void pressButton() {
        if (command)
            command->execute();
    }
};

int main() {
    // Create the receiver.
    std::shared_ptr<Light> light = std::make_shared<Light>();

    // Create concrete command objects.
    std::shared_ptr<Command> lightOn = std::make_shared<LightOnCommand>(light);
    std::shared_ptr<Command> lightOff = std::make_shared<LightOffCommand>(light);

    // Create the invoker.
    RemoteControl remote;

    // Turn the light on.
    remote.setCommand(lightOn);
    remote.pressButton();  // Output: The light is on.

    // Turn the light off.
    remote.setCommand(lightOff);
    remote.pressButton();  // Output: The light is off.

    return 0;
}
