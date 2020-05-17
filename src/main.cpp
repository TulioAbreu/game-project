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
static Camera& gCamera = *Camera::getInstance();

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

    Vector2f contextSize = {WINDOW_WIDTH, WINDOW_HEIGHT};
    Vector2f halfContextSize = contextSize*0.5f;

    gCamera.setGlobalPosition({halfContextSize.x, halfContextSize.y});
    gCamera.fixToEntity(gEntities.getEntityByName("player"));



    while (game.getIsRunning() && window.isOpen()) {
        window.handleWindowEvents(contextSize, halfContextSize);

        for (size_t i = 0; i < gEntities.size(); ++i) {
            gEntities.at(i).update();
        }

        window.clear();

        for (size_t i = 0; i < gEntities.size(); ++i) {
            Rectangle currentEntityRect = gEntities.at(i).getHitbox();
            if (gCamera.isRectangleVisible(currentEntityRect, contextSize)) {
                window.drawRectangle(gCamera.getRelativeRectangle(currentEntityRect, halfContextSize));
            }
        }

        window.display();
    }

    return 0;
}
