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
#include "sprite-manager.hpp"
#include "console.hpp"

#include "../third-party/json.hpp"
#include <fstream>

#include "particle.hpp"
#include "color.hpp"

static Config& gConfig = *Config::getInstance();
static Entities& gEntities = *Entities::getInstance();
static Keyboard& gKeyboard = *Keyboard::getInstance();
static Camera& gCamera = *Camera::getInstance();
static SpriteManager& gSpriteManager = *SpriteManager::getInstance();
static Console& gConsole = *Console::getInstance();

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
    Scene scene (Path("data/scenes/scene_01.json"), true);

    Vector2f contextSize = {WINDOW_WIDTH, WINDOW_HEIGHT};
    Vector2f halfContextSize = contextSize*0.5f;

    gCamera.setGlobalPosition({halfContextSize.x, halfContextSize.y});
    gCamera.fixToEntity(gEntities.getEntityByName("player"));

    Particles particles;

    while (game.getIsRunning() && window.isOpen()) {
        window.handleWindowEvents(contextSize, halfContextSize);

        for (size_t i = 0; i < gEntities.size(); ++i) {
            gEntities.at(i).update();
        }
        gConsole.render();
        window.clear();

        for (size_t i = 0; i < gEntities.size(); ++i) {
            Entity entity = gEntities.at(i);
            Rectangle currentEntityRect = entity.getHitbox();
            if (gCamera.isRectangleVisible(currentEntityRect, contextSize)) {
                window.drawSprite(entity.getSpriteId(), gCamera.getRelativeRectangle(currentEntityRect, halfContextSize));
            }
        }

        particles.update();
        sf::RectangleShape currentParticleDrawing;
        Rectangle currentParticleRectangle;
        Color color("#FFFF00");
        currentParticleDrawing.setFillColor(sf::Color(color.red, color.green, color.blue));
        currentParticleRectangle.height = 1;
        currentParticleRectangle.width = 1;
        for (auto particle : particles.particles) {
            currentParticleRectangle.positionX = particle.position.x;
            currentParticleRectangle.positionY = particle.position.y;
            window.drawRectangle(gCamera.getRelativeRectangle(currentParticleRectangle, halfContextSize));
        }

        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
