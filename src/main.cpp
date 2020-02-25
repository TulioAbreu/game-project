#include <SFML/Graphics.hpp>
#include <vector>

#include "window.hpp"
#include "camera.hpp"
#include "entity.hpp"
#include "scene.hpp"
#include "entities.hpp"
#include "physics_engine.hpp"

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

    const int WINDOW_WIDTH = 1900;
    const int WINDOW_HEIGHT = 1080;
    const char WINDOW_TITLE[] = "GameProject";

    Window window (WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    Scene scene;
    Entities* entitiesPtr = scene.getEntities();
    PhysicsEngine physicsEngine;

    Camera* mainCamera = new Camera();
    mainCamera->setGlobalPosition({320, 240});

    const Vector2f contextSize = {WINDOW_WIDTH, WINDOW_HEIGHT};
    const Vector2f halfContextSize = contextSize*0.5f;

    while (game.getIsRunning() && window.isOpen()) {
        window.handleWindowEvents();

        for (int i = 0; i < entitiesPtr->size(); ++i) {
            entitiesPtr->at(i)->update();
        }
        physicsEngine.update(entitiesPtr, 1.f/60.f);  // TODO: Replace this placeholder deltaTime

        const float CAMERA_SPEED = 1;
        const float ZOOM_SPEED = 0.01;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            mainCamera->setGlobalPosition(mainCamera->getGlobalPosition() + Vector2f(0, -CAMERA_SPEED));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            mainCamera->setGlobalPosition(mainCamera->getGlobalPosition() + Vector2f(0, +CAMERA_SPEED));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            mainCamera->setGlobalPosition(mainCamera->getGlobalPosition() + Vector2f(-CAMERA_SPEED, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            mainCamera->setGlobalPosition(mainCamera->getGlobalPosition() + Vector2f(+CAMERA_SPEED, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            mainCamera->setScale(mainCamera->getScale() + ZOOM_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            mainCamera->setScale(mainCamera->getScale() - ZOOM_SPEED);
        }

        window.clear();

        for (int i = 0; i < entitiesPtr->size(); ++i) {
            const Rectangle currentEntityRect = entitiesPtr->at(i)->getHitbox();

            if (mainCamera->isRectangleVisible(currentEntityRect, contextSize)) {
                window.drawRectangle(mainCamera->getRelativeRectangle(currentEntityRect, halfContextSize));
            }
        }

        window.display();
    }

    return 0;
}
