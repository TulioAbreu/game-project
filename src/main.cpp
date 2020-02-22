#include <SFML/Graphics.hpp>
#include <vector>

class Window {
    sf::Event mEvent;
    sf::RectangleShape mRect;

    public:
    sf::RenderWindow mWindow;

    public:
    Window(int width, int height, std::string title) : mWindow(sf::VideoMode(width, height), title) {
        mWindow.setFramerateLimit(60);
    }
    virtual ~Window() = default;

    void handleWindowEvents() {
        while (mWindow.pollEvent(mEvent)) {
            if (mEvent.type == sf::Event::Closed) {
                // TODO: Maybe add some kind of callback to window class?
                mWindow.close();
            }
        }
    }

    void clear() { mWindow.clear(); }

    void display() { mWindow.display(); }

    bool isOpen() { return mWindow.isOpen(); }
};

struct Rectangle {
    float width, height;
    float positionX, positionY;
};

class Entity {
    private:
    Rectangle mHitbox;

    public:
    Entity() {
        mHitbox = {0, 0, 0, 0};
    }

    Entity(float width, float height, float posX, float posY) {
        mHitbox = {width, height, posX, posY};
    }

    void setHitboxSize(float width, float height) {
        mHitbox.width = width;
        mHitbox.height = height;
    }

    void setHitboxPosition(float x, float y) {
        mHitbox.positionX = x;
        mHitbox.positionY = y;
    }

    float getHitboxPositionX() { return mHitbox.positionX; }
    float getHitboxPositionY() { return mHitbox.positionY; }

    virtual void update() {}

    inline Rectangle getHitbox() { return mHitbox; }
};

class Game {
    bool mIsRunning;

    public:
    Game() = default;
    virtual ~Game() = default;

    void setIsRunning(const bool value) { mIsRunning = value; }
    bool getIsRunning() const { return mIsRunning; }
};

class Camera {
    sf::RenderWindow* mWindowPtr;
    sf::RectangleShape mRect;
    sf::Vector2u mWindowSize;
    sf::Vector2f mGlobalPosition;
    sf::Vector2f mWindowCenter;
    Entity* mFixedEntityPtr;

    private:
    inline void draw(sf::Drawable& drawable) {
        if (!mWindowPtr) {
            return;
        }

        mWindowPtr->draw(drawable);
    }

    public:
    Camera() {
        mWindowPtr = nullptr;
        mFixedEntityPtr = nullptr;
        mGlobalPosition = {0, 0};
        mWindowSize = {0, 0};
        mWindowCenter = {0, 0};
    }
 
    void setGlobalPosition(const float posX, const float posY) { 
        mGlobalPosition = {posX, posY};
    }

    void fixToEntity(Entity* entity) {
        mFixedEntityPtr = entity;
    }

    float getGlobalPositionX() const { 
        if (mFixedEntityPtr) {
            return mFixedEntityPtr->getHitbox().positionX;
        }

        return mGlobalPosition.x; 
    }

    float getGlobalPositionY() const { 
        if (mFixedEntityPtr) {
            return mFixedEntityPtr->getHitbox().positionY;
        }

        return mGlobalPosition.y; 
    }

    void setWindow(Window* window) { 
        if (!window) {
            return;
        }

        mWindowPtr = &window->mWindow;
        mWindowSize = mWindowPtr->getSize();
        mWindowCenter = {mWindowSize.x*0.5f, mWindowSize.y*0.5f};
    }

    void drawCameraPosition() {
        sf::CircleShape circle;
        circle.setFillColor(sf::Color::Red);
        circle.setRadius(5);
        circle.setPosition(mWindowCenter);

        draw(circle);
    }

    void drawRectangle(const Rectangle rectangle) {
        // Lets start with 1.0 scale
        mRect.setSize(sf::Vector2f(rectangle.width, rectangle.height));

        // Lets suppose camera is always on screen center
        if (mFixedEntityPtr) {
            const sf::Vector2f globalPosition (mFixedEntityPtr->getHitbox().positionX, mFixedEntityPtr->getHitbox().positionY);
            mRect.setPosition(sf::Vector2f(rectangle.positionX, rectangle.positionY) - (globalPosition-mWindowCenter));
        }
        else {
            mRect.setPosition(sf::Vector2f(rectangle.positionX, rectangle.positionY) - (mGlobalPosition-mWindowCenter));
        }

        mRect.setFillColor(sf::Color(0,0,0,0));
        mRect.setOutlineColor(sf::Color::Red);
        mRect.setOutlineThickness(2);

        draw(mRect);
    }
};

int main() {
    Game game;
    game.setIsRunning(true);

    Window window (640, 480, "GameProject");
    Camera camera;
    camera.setWindow(&window);
    camera.setGlobalPosition(0, 0);

    std::vector<Entity> entities = {
        Entity(200, 200, 0, 0),
        Entity(10, 10, 100, 100),
        Entity(10, 10, 320, 240),
        Entity(50, 50, 200, 300)
    };

    while (game.getIsRunning() && window.isOpen()) {
        window.handleWindowEvents();

        for (auto entity : entities) {
            entity.update();
        }

        constexpr float CAMERA_SPEED = 1.0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            camera.setGlobalPosition(camera.getGlobalPositionX(), camera.getGlobalPositionY()-CAMERA_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            camera.setGlobalPosition(camera.getGlobalPositionX(), camera.getGlobalPositionY()+CAMERA_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            camera.setGlobalPosition(camera.getGlobalPositionX()-CAMERA_SPEED, camera.getGlobalPositionY());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            camera.setGlobalPosition(camera.getGlobalPositionX()+CAMERA_SPEED, camera.getGlobalPositionY());
        }

        window.clear();
        for (auto entity : entities) {
            camera.drawRectangle(entity.getHitbox());
        }
        camera.drawCameraPosition();
        window.display();
    }

    return 0;
}
