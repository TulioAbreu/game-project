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

    void readSceneFile() {
        // This is just a placeholder
        mEntities.add(Entity(200, 200, 0, 0));
        mEntities.add(Entity(10, 10, 100, 100));
        mEntities.add(Entity(10, 10, -100, -100));

        mEntities.add(Entity(10, 10, 310, 0));
        mEntities.add(Entity(50, 50, 200, 300));
    }
    public:
    Scene() {
        readSceneFile();
    }

    void update() {
        for (int i = 0; i < mEntities.size(); ++i) {
            mEntities.at(i).update();
        }
    }

    Entities& getEntities() {
        return mEntities;
    }
};

int main() {
    Game game;
    game.setIsRunning(true);

    const int WINDOW_WIDTH = 1900;
    const int WINDOW_HEIGHT = 1080;
    const char WINDOW_TITLE[] = "GameProject";

    Window window (WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    Scene scene;
    Entities* entitiesPtr = &scene.getEntities();

    Camera* mainCamera = new Camera();
    mainCamera->setGlobalPosition({320, 240});

    const Vector2f contextSize = {WINDOW_WIDTH, WINDOW_HEIGHT};
    const Vector2f halfContextSize = contextSize*0.5f;

    while (game.getIsRunning() && window.isOpen()) {
        window.handleWindowEvents();

        for (int i = 0; i < entitiesPtr->size(); ++i) {
            entitiesPtr->at(i).update();
        }

        const float CAMERA_SPEED = 1;
        const float ZOOM_SPEED = 0.01;
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        //     mainCamera->setGlobalPosition(mainCamera->getGlobalPosition() + Vector2f(0, -CAMERA_SPEED));
        // }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        //     mainCamera->setGlobalPosition(mainCamera->getGlobalPosition() + Vector2f(0, +CAMERA_SPEED));
        // }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        //     mainCamera->setGlobalPosition(mainCamera->getGlobalPosition() + Vector2f(-CAMERA_SPEED, 0));
        // }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        //     mainCamera->setGlobalPosition(mainCamera->getGlobalPosition() + Vector2f(+CAMERA_SPEED, 0));
        // }

        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        //     mainCamera->setScale(mainCamera->getScale() + ZOOM_SPEED);
        // }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        //     mainCamera->setScale(mainCamera->getScale() - ZOOM_SPEED);
        // }

        window.clear();

        for (int i = 0; i < entitiesPtr->size(); ++i) {
            Rectangle currentEntityRect = entitiesPtr->at(i).getHitbox();
            if (mainCamera->isRectangleVisible(currentEntityRect, contextSize)) {
                window.drawRectangle(mainCamera->getRelativeRectangle(currentEntityRect, halfContextSize));
            }
        }

        window.display();
    }

    return 0;
}
