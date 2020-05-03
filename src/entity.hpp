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
    Entity();
    Entity(std::vector<Script*> scripts);
    Entity(float width, float height, float posX, float posY, std::vector<Script*> scripts);
    ~Entity();
    void setHitboxSize(float width, float height);
    void setHitboxPosition(float x, float y);
    float getHitboxPositionX();
    float getHitboxPositionY();
    void setHitboxWidth(float value);
    void setHitboxHeight(float value);

    float getHitboxWidth();
    float getHitboxHeight();

    void update();
    Rectangle getHitbox();
    int getID();
};

#endif