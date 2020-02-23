#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "rectangle.hpp"

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

#endif