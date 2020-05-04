#define SDL_MAIN_HANDLED

#include <vector>
#include <SDL2/SDL.h>
#include "log.hpp"
#include "scriptManager.hpp"
#include "keyboard.hpp"
#include "window.hpp"
#include "camera.hpp"
#include "entity.hpp"
#include "scene.hpp"
#include "entity-container.hpp"

static Keyboard* gKeyboard = Keyboard::getInstance();

class Game {
    bool mIsRunning;

    public:
    Game() = default;
    virtual ~Game() = default;

    void setIsRunning(const bool value) { mIsRunning = value; }
    bool getIsRunning() const { return mIsRunning; }
};


void handleKeyboard(Keyboard* keyboard, Camera* mainCamera) {
    const float CAMERA_SPEED = 1;
    const float ZOOM_SPEED = 0.01;
    
    // if (gKeyboard->isKeyPressed("UP")) {
    //     mainCamera->setGlobalPosition(mainCamera->getGlobalPosition() + Vector2f(0, -CAMERA_SPEED));
    // }

    // if (gKeyboard->isKeyPressed("DOWN")) {
    //     mainCamera->setGlobalPosition(mainCamera->getGlobalPosition() + Vector2f(0, +CAMERA_SPEED));
    // }

    // if (gKeyboard->isKeyPressed("LEFT")) {
    //     mainCamera->setGlobalPosition(mainCamera->getGlobalPosition() + Vector2f(-CAMERA_SPEED, 0));
    // }

    // if (gKeyboard->isKeyPressed("RIGHT")) {
    //     mainCamera->setGlobalPosition(mainCamera->getGlobalPosition() + Vector2f(+CAMERA_SPEED, 0));
    // }

    if (gKeyboard->isKeyPressed("W")) {
         mainCamera->setScale(mainCamera->getScale() + ZOOM_SPEED);
    }

    if (gKeyboard->isKeyPressed("S")) {
        mainCamera->setScale(mainCamera->getScale() - ZOOM_SPEED);
    }
}

int main() {
    Game game;
    game.setIsRunning(true);

    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    const char WINDOW_TITLE[] = "GameProject";

    Window window (WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    Keyboard keyboard;
    Scene scene;

    Entities* gEntities = (Entities*) Entities::getInstance();

    Camera* mainCamera = new Camera();
    mainCamera->setGlobalPosition({320, 240});

    const Vector2f contextSize = {WINDOW_WIDTH, WINDOW_HEIGHT};
    const Vector2f halfContextSize = contextSize*0.5f;


    while (game.getIsRunning() && window.isOpen()) {
        window.handleWindowEvents();

        for (size_t i = 0; i < gEntities->size(); ++i) {
            gEntities->at(i).update();
        }

        handleKeyboard(&keyboard, mainCamera);

        window.clear();

        for (size_t i = 0; i < gEntities->size(); ++i) {
            Rectangle currentEntityRect = gEntities->at(i).getHitbox();
            if (mainCamera->isRectangleVisible(currentEntityRect, contextSize)) {
                window.drawRectangle(mainCamera->getRelativeRectangle(currentEntityRect, halfContextSize));
            }
        }

        window.display();
    }

    return 0;
}
