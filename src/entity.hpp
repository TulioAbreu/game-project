#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>

#include "rectangle.hpp"
#include "scriptManager.hpp"

class Entity {
    private:
    static int nextEntityID;
    int mID;
    Rectangle mHitbox;
    std::vector<Script*> mScripts;

    public:
    Entity() {
        mID = nextEntityID++;
        mHitbox = {0, 0, 0, 0};
    }

    Entity(std::vector<Script*> scripts) {
        mID = nextEntityID++;
        mHitbox = {0, 0, 0, 0};
        mScripts = scripts;

        for (auto script : mScripts) {
            script->onStart(mID);
        }
    }

    Entity(float width, float height, float posX, float posY, std::vector<Script*> scripts) {
        mID = nextEntityID++;

        mHitbox = {width, height, posX, posY};
        mScripts = scripts;

        for (auto script : mScripts) {
            script->onStart(mID);
        }
    }

    ~Entity() {
        for (auto script : mScripts) {
            script->onDestroy(mID);
        }

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

    void update() {
        for (auto script : mScripts) {
            script->onUpdate(mID);
        }
    }

    inline Rectangle getHitbox() { return mHitbox; }
};

int Entity::nextEntityID = 0;
#endif