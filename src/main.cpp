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
    float mScale;
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

    sf::Vector2f getScaledSize(const Rectangle rectangle) {
        return {rectangle.width*mScale, rectangle.height*mScale};
    }

    public:
    Camera() {
        mScale = 1;
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

    void setScale(float value) { 
        if (value < 0.01) { 
            mScale = 0.01; 
            return;
        }
        mScale = value; 
    }

    float getScale() { return mScale; }

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

    // sf::Vector2f getScaledScreenCoordinates(sf::Vector2f screenCoordinates) {
    //     return {screenCoordinates.x*mScale, screenCoordinates.y*mScale};
    // }

    sf::Vector2f getScreenCoordinates(Rectangle rectangle) {
        sf::Vector2f screenCoordinates;
        if (mFixedEntityPtr) {
            const Rectangle fixedEntityHitbox = mFixedEntityPtr->getHitbox();
            const sf::Vector2f globalPosition = {fixedEntityHitbox.positionX, fixedEntityHitbox.positionY};

            screenCoordinates = sf::Vector2f(rectangle.positionX*mScale, rectangle.positionY*mScale) - (globalPosition*mScale-mWindowCenter);
        }
        else {
            screenCoordinates = sf::Vector2f(rectangle.positionX*mScale, rectangle.positionY*mScale) - (mGlobalPosition*mScale-mWindowCenter);
        }

        // return getScaledScreenCoordinates(screenCoordinates);
        return screenCoordinates;
    }

    void drawRectangle(const Rectangle rectangle) {
        mRect.setSize(getScaledSize(rectangle));

        // Lets suppose camera is always on screen center
        mRect.setPosition(getScreenCoordinates(rectangle));

        mRect.setFillColor(sf::Color(0,0,0,0));
        mRect.setOutlineColor(sf::Color::Red);
        const float thickness = (2*mScale > 0.8)? 2*mScale:0.8;
        mRect.setOutlineThickness(thickness);

        draw(mRect);
    }
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

int main() {
    Game game;
    game.setIsRunning(true);

    constexpr int WINDOW_WIDTH = 640;
    constexpr int WINDOW_HEIGHT = 480;
    constexpr char WINDOW_TITLE[] = "GameProject";

    Window window (WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    Camera camera;
    camera.setWindow(&window);
    camera.setGlobalPosition(0, 0);

    Entities entities;
    entities.add(Entity(200, 200, 0, 0));
    entities.add(Entity(10, 10, 100, 100));
    entities.add(Entity(10, 10, 320, 240));
    entities.add(Entity(50, 50, 200, 300));

    while (game.getIsRunning() && window.isOpen()) {
        window.handleWindowEvents();

        for (int i = 0; i < entities.size(); ++i) {
            entities.at(i).update();
        }

        constexpr float CAMERA_SPEED = 1.0;
        constexpr float ZOOM_SPEED = 0.01;
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            camera.setScale(camera.getScale()+ZOOM_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            camera.setScale(camera.getScale()-ZOOM_SPEED);
        }

        window.clear();
        for (int i = 0; i < entities.size(); ++i) {
            camera.drawRectangle(entities.at(i).getHitbox());
        }

        camera.drawCameraPosition();
        window.display();
    }

    return 0;
}
