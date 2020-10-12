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
#include "../third-party/json.hpp"
#include "console/core.hpp"

class Game {
    Config* mConfig;
    Entities::Container* mEntities;
    Scene* mScene;
    Keyboard* mKeyboard;
    Graphics::Camera* mCamera;
    Console::Core* mConsole;
    Graphics::Window* mWindow;
    std::string mGameWindowTitle;
    Vector2f mGameWindowSize;
    bool mIsRunning;

public:
    Game() {
        mConfig = Config::getInstance();
        mScene = nullptr;
        mEntities = Entities::Container::getInstance();
        mKeyboard = Keyboard::getInstance();
        mCamera = Graphics::Camera::getInstance();
        mConsole = new Console::Core();
        mWindow = nullptr;
    }

    ~Game() {
        delete mWindow;
        delete mConsole;
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
        mScene = new Scene(mConfig->getDefaultScene(), true);
        // TODO: Camera should be inside Scene (class&file), and there it should be attached to some script or entity

        while (getIsRunning() && mWindow->isOpen()) {
            handleEvents();
            mConsole->update();
            mScene->update();
            render();
        }
    }

private:
    void handleEvents() {
        mWindow->handleWindowEvents(mGameWindowSize);
    }

    void render() {
        if (!mWindow->isOpen()) {
            return;
        }

        mWindow->clear();
        const Vector2f halfContextSize = mGameWindowSize * .5f;
        mWindow->drawScene(mScene, mCamera, halfContextSize);
        mConsole->render();
        mWindow->display();
    }
};

int main() {
    Game game;
    game.start();
    return 0;
}
