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
        mHitbox = {{0, 0}, {0, 0}};
        mPhysics = {true, {0, 0}, {0, 0}, &mHitbox};
    }

    Entity(float width, float height, float posX, float posY) {
        mHitbox = {{width, height}, {posX, posY}};
        mPhysics = {true, {0, 0}, {0, 0}, &mHitbox };
    }

    void setHitboxSize(float width, float height) {
        mHitbox.size = {width, height};
    }

    void setHitboxPosition(float x, float y) {
        mHitbox.position = {x, y};
    }

    Physics& getPhysicsData() { return mPhysics; }

    float getHitboxPositionX() { return mHitbox.position.x; }
    float getHitboxPositionY() { return mHitbox.position.y; }

    virtual void update() {}
    virtual void onCollision(Collision collision) {
        std::cout << "Called on collision!" << std::endl;
    }

    inline Rectangle& getHitbox() { return mHitbox; }
};

#endif