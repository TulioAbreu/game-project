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

class Scene {
private:
    Entities mEntities;
    Camera mCamera;

    void readSceneFile() {
        // This is just a placeholder
        mEntities.add(Entity(200, 200, 0, 0));
        mEntities.add(Entity(10, 10, 100, 100));
        mEntities.add(Entity(10, 10, 320, 240));
        mEntities.add(Entity(50, 50, 200, 300));
    }
public:
    Scene(Window* windowPtr) {
        mCamera.setWindow(windowPtr);
        mCamera.setGlobalPosition(0, 0);
        readSceneFile();
    }

    void update() {
        for (int i = 0; i < mEntities.size(); ++i) {
            mEntities.at(i).update();
        }

        constexpr float CAMERA_SPEED = 1.0;
        constexpr float ZOOM_SPEED = 0.01;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            mCamera.setGlobalPosition(mCamera.getGlobalPositionX(), mCamera.getGlobalPositionY()-CAMERA_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            mCamera.setGlobalPosition(mCamera.getGlobalPositionX(), mCamera.getGlobalPositionY()+CAMERA_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            mCamera.setGlobalPosition(mCamera.getGlobalPositionX()-CAMERA_SPEED, mCamera.getGlobalPositionY());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            mCamera.setGlobalPosition(mCamera.getGlobalPositionX()+CAMERA_SPEED, mCamera.getGlobalPositionY());
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            mCamera.setScale(mCamera.getScale()+ZOOM_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            mCamera.setScale(mCamera.getScale()-ZOOM_SPEED);
        }
    }

    void draw() {
        for (int i = 0; i < mEntities.size(); ++i) {
            mCamera.drawRectangle(mEntities.at(i).getHitbox());
        }
        mCamera.drawCameraPosition();
    }

    Camera& getCamera() {
        return mCamera;
    }

    Entities& getEntities() {
        return mEntities;
    }
};

int main() {
    Game game;
    game.setIsRunning(true);

    constexpr int WINDOW_WIDTH = 640;
    constexpr int WINDOW_HEIGHT = 480;
    constexpr char WINDOW_TITLE[] = "GameProject";

    Window window (WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    Scene scene (&window);

    while (game.getIsRunning() && window.isOpen()) {
        window.handleWindowEvents();
        scene.update();

        window.clear();
        scene.draw();
        window.display();
    }

    return 0;
}
