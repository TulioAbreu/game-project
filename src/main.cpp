#include <vector>
#include <fstream>
#include "utils/log/log.hpp"
#include "script-manager.hpp"
#include "keyboard.hpp"
#include "graphics/window/window.hpp"
#include "graphics/camera/camera.hpp"
#include "config.hpp"
#include "entity.hpp"
#include "scene/scene.hpp"
#include "entities/container/container.hpp"
#include "sprite-manager.hpp"
#include "console.hpp"
#include "../third-party/json.hpp"

class Game {
    Config* mConfig;
    Entities::Container* mEntities;
    Keyboard* mKeyboard;
    Graphics::Camera* mCamera;
    SpriteManager* mSpriteManager;
    Console* mConsole;
    Graphics::Window* mWindow;
    std::string mGameWindowTitle;
    Vector2f mGameWindowSize;
    bool mIsRunning;

public:
    Game() {
        mConfig = Config::getInstance();
        mEntities = Entities::Container::getInstance();
        mKeyboard = Keyboard::getInstance();
        mCamera = Graphics::Camera::getInstance();
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
        mGameWindowTitle = mConfig->getWindowTitle();
        mGameWindowSize = mConfig->getWindowSize();
        mWindow = new Graphics::Window(mGameWindowSize.x, mGameWindowSize.y, mGameWindowTitle);

        Scene scene (mConfig->getDefaultScene().value, true);

        mCamera->setGlobalPosition(mGameWindowSize*.5f);
        mCamera->fixToEntity(mEntities->getEntityByName("player"));

        while (getIsRunning() && mWindow->isOpen()) {
            handleEvents();
            update();
            render();
        }
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
        if (!mWindow->isOpen()) {
            return;
        }

        mWindow->clear();
        const Vector2f halfScreen = mGameWindowSize * .5f;
        for (size_t i = 0; i < mEntities->size(); ++i) {
            Entity entity = mEntities->at(i);
            Rectangle currentEntityRect = entity.getHitbox();
            // TODO: (currentRect, visionRect) doesnt work
            if (intersects(mCamera->getVisionRectangle(mWindow->getWindowSize()), currentEntityRect)) {
                mWindow->drawSprite(entity.getSpriteId(), mCamera->getRelativeRectangle(currentEntityRect, halfScreen));
            }
        }
        mConsole->render();
        mWindow->display();
    }
};

int main() {
    Game game;
    game.start();
    return 0;
}
