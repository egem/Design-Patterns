#include <iostream>
#include <string>
using namespace std;

// Subject Interface: Image
class Image {
public:
    virtual void display() = 0;
    virtual ~Image() = default;
};

// Real Subject: The actual large image class
class RealImage : public Image {
private:
    string filename;

public:
    RealImage(string file) : filename(file) {
        loadImage();
    }

    void loadImage() const {
        cout << "Loading image: " << filename << endl;
    }

    void display() override {
        cout << "Displaying image: " << filename << endl;
    }
};

// Proxy: Controls access to the RealImage
class ProxyImage : public Image {
private:
    string filename;
    RealImage* realImage;

public:
    ProxyImage(string file) : filename(file), realImage(nullptr) {}

    ~ProxyImage() {
        delete realImage;
    }

    void display() override {
        if (!realImage) {
            realImage = new RealImage(filename); // Lazy loading
        }
        realImage->display();
    }
};

int main() {
    cout << "=== Proxy Pattern: Virtual Image Loading ===" << endl;

    // Client uses Proxy to access the image
    Image* image1 = new ProxyImage("photo1.jpg");
    Image* image2 = new ProxyImage("photo2.jpg");

    // Images are only loaded and displayed when needed
    image1->display(); // Loads and displays the image
    image2->display(); // Loads and displays the image
    image1->display(); // Uses cached loaded image

    delete image1;
    delete image2;

    return 0;
}
