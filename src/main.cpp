#include <vector>
#include "log.hpp"
#include "script-manager.hpp"
#include "keyboard.hpp"
#include "window.hpp"
#include "camera.hpp"
#include "config.hpp"
#include "entity.hpp"
#include "scene.hpp"
#include "entity-container.hpp"

#include "../third-party/json.hpp"
#include <fstream>

static Config& gConfig = *Config::getInstance();
static Entities& gEntities = *Entities::getInstance();
static Keyboard& gKeyboard = *Keyboard::getInstance();

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

    const float WINDOW_WIDTH = gConfig["window"]["width"];
    const float WINDOW_HEIGHT = gConfig["window"]["height"];
    const std::string WINDOW_TITLE = gConfig["window"]["title"];

    Window window (WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.c_str());
    Keyboard keyboard;
    Scene scene;

    Camera* mainCamera = new Camera();
    mainCamera->setGlobalPosition({320, 240});
    mainCamera->fixToEntity(gEntities.getEntityByName("player"));

    const Vector2f contextSize = {WINDOW_WIDTH, WINDOW_HEIGHT};
    const Vector2f halfContextSize = contextSize*0.5f;


    while (game.getIsRunning() && window.isOpen()) {
        window.handleWindowEvents();

        for (size_t i = 0; i < gEntities.size(); ++i) {
            gEntities.at(i).update();
        }

        window.clear();

        for (size_t i = 0; i < gEntities.size(); ++i) {
            Rectangle currentEntityRect = gEntities.at(i).getHitbox();
            if (mainCamera->isRectangleVisible(currentEntityRect, contextSize)) {
                window.drawRectangle(mainCamera->getRelativeRectangle(currentEntityRect, halfContextSize));
            }
        }

        window.display();
    }

    return 0;
}
