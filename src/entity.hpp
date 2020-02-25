#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "rectangle.hpp"
#include "physics.hpp"

#include <iostream>

class Entity {
    private:
    Rectangle mHitbox;
    Physics mPhysics;

    public:
    Entity() {
        mHitbox = {0, 0, 0, 0};
        mPhysics = {true, {0, 0}, {0, 0}, &mHitbox};
    }

    Entity(float width, float height, float posX, float posY) {
        mHitbox = {width, height, posX, posY};
        mPhysics = {true, {0, 0}, {0, 0}, &mHitbox };
    }

    void setHitboxSize(float width, float height) {
        mHitbox.width = width;
        mHitbox.height = height;
    }

    void setHitboxPosition(float x, float y) {
        mHitbox.positionX = x;
        mHitbox.positionY = y;
    }

    Physics& getPhysicsData() { return mPhysics; }

    float getHitboxPositionX() { return mHitbox.positionX; }
    float getHitboxPositionY() { return mHitbox.positionY; }

    virtual void update() {}
    virtual void onCollision(Collision collision) {
        std::cout << "Called on collision!" << std::endl;
    }

    inline Rectangle& getHitbox() { return mHitbox; }
};

#endif