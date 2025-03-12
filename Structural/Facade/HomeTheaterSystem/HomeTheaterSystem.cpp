#include <iostream>
using namespace std;

// Subsystem 1: Amplifier
class Amplifier {
public:
    void on() { cout << "Amplifier: ON" << endl; }
    void off() { cout << "Amplifier: OFF" << endl; }
};

// Subsystem 2: DVD Player
class DVDPlayer {
public:
    void play() { cout << "DVD Player: Playing movie" << endl; }
    void stop() { cout << "DVD Player: Stopped" << endl; }
};

// Subsystem 3: Projector
class Projector {
public:
    void on() { cout << "Projector: ON" << endl; }
    void off() { cout << "Projector: OFF" << endl; }
};

// Subsystem 4: Lights
class Lights {
public:
    void dim() { cout << "Lights: Dimming to 30%" << endl; }
    void brighten() { cout << "Lights: Brightening" << endl; }
};

// Facade: Home Theater
class HomeTheaterFacade {
private:
    Amplifier amp;
    DVDPlayer dvd;
    Projector projector;
    Lights lights;

public:
    void watchMovie() {
        cout << "Starting Movie Mode..." << endl;
        lights.dim();
        projector.on();
        amp.on();
        dvd.play();
    }

    void endMovie() {
        cout << "Shutting Down Movie Mode..." << endl;
        dvd.stop();
        amp.off();
        projector.off();
        lights.brighten();
    }
};

int main() {
    HomeTheaterFacade homeTheater;

    cout << "\n=== Movie Night ===\n";
    homeTheater.watchMovie();

    cout << "\n=== Movie Over ===\n";
    homeTheater.endMovie();

    return 0;
}

