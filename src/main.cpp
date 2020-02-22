#include <SFML/Graphics.hpp>

class Game {
    bool mIsRunning;

public:
    Game() = default;
    virtual ~Game() = default;

    void setIsRunning(const bool value) { mIsRunning = value; }
    bool getIsRunning() const { return mIsRunning; }
};

class Window {
    sf::RenderWindow mWindow;
    sf::Event mEvent;
    sf::RectangleShape mRect;

public:
    Window(int width, int height, std::string title) : mWindow(sf::VideoMode(width, height), title) {}
    virtual ~Window() = default;

    void handleWindowEvents() {
        while (mWindow.pollEvent(mEvent)) {
            if (mEvent.type == sf::Event::Closed) {
                // TODO: Maybe add some kind of callback to window class?
                mWindow.close();
            }
        }
    }

    void clear() { mWindow.clear(); }

    void display() { mWindow.display(); }

    bool isOpen() { return mWindow.isOpen(); }
};

struct Rectangle {
    float width, height;
    float positionX, positionY;
};


int main() {
    Game game;
    game.setIsRunning(true);

    Window window (640, 480, "GameProject");

    while (game.getIsRunning() && window.isOpen()) {
        window.handleWindowEvents();

        window.clear();
        window.display();
    }

    return 0;
}