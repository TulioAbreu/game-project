#include <SFML/Graphics.hpp>

class Game {
    bool mIsRunning;

public:
    Game() = default;
    virtual ~Game() = default;

    void setIsRunning(const bool value) { mIsRunning = value; }
    bool getIsRunning() const { return mIsRunning; }
};

int main() {
    Game game;
    game.setIsRunning(true);

    using namespace sf;
    RenderWindow window (VideoMode(640, 480), "GameProject");

    while (game.getIsRunning()) {
        Event windowEvent;
        while (window.pollEvent(windowEvent)) {
            if (windowEvent.type == Event::Closed) {
                game.setIsRunning(false);
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}