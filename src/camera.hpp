#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include "window.hpp"
#include "rectangle.hpp"
#include "entity.hpp"


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

        return screenCoordinates;
    }

    void drawRectangle(const Rectangle rectangle) {
        mRect.setSize(getScaledSize(rectangle));
        mRect.setPosition(getScreenCoordinates(rectangle));

        mRect.setFillColor(sf::Color(0,0,0,0));
        mRect.setOutlineColor(sf::Color::Red);
        const float thickness = (2*mScale > 0.8)? 2*mScale:0.8;
        mRect.setOutlineThickness(thickness);

        draw(mRect);
    }
};


#endif
