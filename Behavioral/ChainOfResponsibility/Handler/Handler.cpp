#include <iostream>
#include <memory>

// Abstract Handler interface
class Handler {
protected:
    std::shared_ptr<Handler> nextHandler;
public:
    // Set the next handler in the chain
    void setNext(const std::shared_ptr<Handler>& handler) {
        nextHandler = handler;
    }

    // Virtual method to handle the request; if not handled, pass it to the next handler
    virtual void handleRequest(int request) {
        if (nextHandler) {
            nextHandler->handleRequest(request);
        } else {
            std::cout << "No handler available for request: " << request << std::endl;
        }
    }

    virtual ~Handler() {}
};

// Concrete Handler 1 handles requests between 0 and 9
class ConcreteHandler1 : public Handler {
public:
    void handleRequest(int request) override {
        if (request >= 0 && request < 10) {
            std::cout << "ConcreteHandler1 handled request " << request << std::endl;
        } else if (nextHandler) {
            nextHandler->handleRequest(request);
        } else {
            std::cout << "Request " << request << " not handled." << std::endl;
        }
    }
};

// Concrete Handler 2 handles requests between 10 and 19
class ConcreteHandler2 : public Handler {
public:
    void handleRequest(int request) override {
        if (request >= 10 && request < 20) {
            std::cout << "ConcreteHandler2 handled request " << request << std::endl;
        } else if (nextHandler) {
            nextHandler->handleRequest(request);
        } else {
            std::cout << "Request " << request << " not handled." << std::endl;
        }
    }
};

// Default Handler handles any requests not processed by earlier handlers
class DefaultHandler : public Handler {
public:
    void handleRequest(int request) override {
        std::cout << "DefaultHandler handled request " << request << std::endl;
    }
};

int main() {
    // Create handlers using smart pointers
    std::shared_ptr<Handler> handler1 = std::make_shared<ConcreteHandler1>();
    std::shared_ptr<Handler> handler2 = std::make_shared<ConcreteHandler2>();
    std::shared_ptr<Handler> defaultHandler = std::make_shared<DefaultHandler>();

    // Build the chain: handler1 -> handler2 -> defaultHandler
    handler1->setNext(handler2);
    handler2->setNext(defaultHandler);

    // Example requests
    int requests[] = {5, 14, 25};

    for (int request : requests) {
        std::cout << "Processing request: " << request << std::endl;
        handler1->handleRequest(request);
    }

    return 0;
}
