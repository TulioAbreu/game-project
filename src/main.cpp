#include <SFML/Graphics.hpp>
#include <vector>

#include "window.hpp"
#include "camera.hpp"
#include "entity.hpp"


class Game {
    bool mIsRunning;

    public:
    Game() = default;
    virtual ~Game() = default;

    void setIsRunning(const bool value) { mIsRunning = value; }
    bool getIsRunning() const { return mIsRunning; }
};


class Entities {
    // TODO: implement a more sophisticated data structure 
    private:
    std::vector<Entity> entities;

    public:
    size_t size() {
        return entities.size();
    }

    Entity at(int index) {
        return entities.at(index);
    }

    void add(Entity entity) {
        entities.push_back(entity);
    }

    bool remove(int index) {
        if (entities.empty()) {
            return false;
        } 
        if (index < 0 && index >= entities.size()) {
            return false;
        }

        entities.erase(entities.begin() + index);
        return true;
    }
};

int main() {
    Game game;
    game.setIsRunning(true);

    constexpr int WINDOW_WIDTH = 640;
    constexpr int WINDOW_HEIGHT = 480;
    constexpr char WINDOW_TITLE[] = "GameProject";

    Window window (WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    Camera camera;
    camera.setWindow(&window);
    camera.setGlobalPosition(0, 0);

    Entities entities;
    entities.add(Entity(200, 200, 0, 0));
    entities.add(Entity(10, 10, 100, 100));
    entities.add(Entity(10, 10, 320, 240));
    entities.add(Entity(50, 50, 200, 300));

    while (game.getIsRunning() && window.isOpen()) {
        window.handleWindowEvents();

        for (int i = 0; i < entities.size(); ++i) {
            entities.at(i).update();
        }

        constexpr float CAMERA_SPEED = 1.0;
        constexpr float ZOOM_SPEED = 0.01;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            camera.setGlobalPosition(camera.getGlobalPositionX(), camera.getGlobalPositionY()-CAMERA_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            camera.setGlobalPosition(camera.getGlobalPositionX(), camera.getGlobalPositionY()+CAMERA_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            camera.setGlobalPosition(camera.getGlobalPositionX()-CAMERA_SPEED, camera.getGlobalPositionY());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            camera.setGlobalPosition(camera.getGlobalPositionX()+CAMERA_SPEED, camera.getGlobalPositionY());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            camera.setScale(camera.getScale()+ZOOM_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            camera.setScale(camera.getScale()-ZOOM_SPEED);
        }

        window.clear();
        for (int i = 0; i < entities.size(); ++i) {
            camera.drawRectangle(entities.at(i).getHitbox());
        }

        camera.drawCameraPosition();
        window.display();
    }

    return 0;
}
