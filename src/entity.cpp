#include "entity.hpp"

int Entity::nextEntityID = 0;

Entity::Entity() {
    mID = nextEntityID++;
    mHitbox = {0, 0, 0, 0};
}

Entity::Entity(std::vector<Script*> scripts) {
    mID = nextEntityID++;
    mHitbox = {0, 0, 0, 0};
    mScripts = scripts;

    for (auto script : mScripts) {
        script->onStart(mID);
    }
}

Entity::Entity(float width, float height, float posX, float posY, std::vector<Script*> scripts) {
    mID = nextEntityID++;

    mHitbox = {width, height, posX, posY};
    mScripts = scripts;

    for (auto script : mScripts) {
        script->onStart(mID);
    }
}

Entity::~Entity() {
    for (auto script : mScripts) {
        script->onDestroy(mID);
    }
}

void Entity::setHitboxSize(float width, float height) {
    mHitbox.width = width;
    mHitbox.height = height;
}

void Entity::setHitboxPosition(float x, float y) {
    mHitbox.positionX = x;
    mHitbox.positionY = y;
}

float Entity::getHitboxPositionX() { 
    return mHitbox.positionX; 
}

float Entity::getHitboxPositionY() { 
    return mHitbox.positionY; 
}

void Entity::update() {
    for (auto script : mScripts) {
        script->onUpdate(mID);
    }
}

Rectangle Entity::getHitbox() { 
    return mHitbox; 
}

int Entity::getID() {
    return mID; 
}

void Entity::setHitboxWidth(float value) {
    mHitbox.width = value;
}

void Entity::setHitboxHeight(float value) {
    mHitbox.height = value;
}
