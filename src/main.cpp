#include <vector>
#include <fstream>
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
#include "filepath.hpp"

class Game {
    Entities* mEntities;
    Keyboard* mKeyboard;
    Camera* mCamera;
    SpriteManager* mSpriteManager;
    Console* mConsole;
    Window* mWindow;

    std::string mGameWindowTitle;
    Vector2f mGameWindowSize;
    bool mIsRunning;

public:
    Game() {
        mEntities = Entities::getInstance();
        mKeyboard = Keyboard::getInstance();
        mCamera = Camera::getInstance();
        mSpriteManager = SpriteManager::getInstance();
        mConsole = Console::getInstance();
        mWindow = nullptr;
    }

    ~Game() {
        delete mWindow;
    }

    void setIsRunning(const bool value) {
        mIsRunning = value;
    }

    bool getIsRunning() const {
        return mIsRunning;
    }

    void start() {
        setIsRunning(true);
        mGameWindowSize = GAME_WINDOW_SIZE;
        mGameWindowTitle = GAME_WINDOW_TITLE;
        mWindow = new Window(mGameWindowSize.x, mGameWindowSize.y, mGameWindowTitle);

        Keyboard keyboard;
        Scene scene (Path("data/scenes/scene_01.json"), true);

        mCamera->setGlobalPosition(mGameWindowSize*.5f);
        mCamera->fixToEntity(mEntities->getEntityByName("player"));

        while (getIsRunning() && mWindow->isOpen()) {
            handleEvents();
            update();
            render();
        }

        ImGui::SFML::Shutdown();
    }

private:
    void handleEvents() {
        mWindow->handleWindowEvents(mGameWindowSize);
    }

    void update() {
        for (size_t i = 0; i < mEntities->size(); ++i) {
            mEntities->at(i).update();
        }
    }

    void render() {
        mConsole->render();
        mWindow->clear();

        for (size_t i = 0; i < mEntities->size(); ++i) {
            Entity entity = mEntities->at(i);
            Rectangle currentEntityRect = entity.getHitbox();
            if (mCamera->isRectangleVisible(currentEntityRect, mGameWindowSize)) {
                mWindow->drawSprite(entity.getSpriteId(), mCamera->getRelativeRectangle(currentEntityRect, mGameWindowSize*0.5f));
            }
        }
        mWindow->display();
    }
};

int main() {
    Game game;
    game.start();
    return 0;
}
