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
}

Entity::Entity(std::string name, float width, float height, float posX, float posY, std::vector<Script*> scripts) {
    mID = nextEntityID++;
    mName = name;
    mHitbox = {width, height, posX, posY};
    mScripts = scripts;
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

void Entity::setHitboxSize(Vector2f size) {
    mHitbox.width = size.x;
    mHitbox.height = size.y;
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

float Entity::getHitboxWidth() {
    return mHitbox.width;
}

float Entity::getHitboxHeight() {
    return mHitbox.height;
}

void Entity::setHitboxPositionX(float value) {
    mHitbox.positionX = value;
}

void Entity::setHitboxPositionY(float value) {
    mHitbox.positionY = value;
}

void Entity::runStartScripts() {
    for (auto script : mScripts) {
        script->onStart(mID);
    }
}

void Entity::setName(std::string name) {
    mName = name;
}

std::string Entity::getName() {
    return mName;
}

void Entity::addScript(Script* script) {
    mScripts.push_back(script);
}

int Entity::getSpriteId() {
    return mSpriteId;
}

void Entity::setSpriteId(size_t spriteId) {
    mSpriteId = spriteId;
}
