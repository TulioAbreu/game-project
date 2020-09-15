#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include <string>

#include "utils/vector2/vector2.hpp"
#include "utils/rectangle/rectangle.hpp"
#include "script-manager.hpp"

class Entity {
    private:
    static int nextEntityID;
    int mID;
    std::string mName;
    Rectangle mHitbox;
    std::vector<Script*> mScripts;
    size_t mSpriteId;

    public:
    Entity();
    Entity(std::vector<Script*> scripts);
    Entity(std::string name, 
           float width,
           float height,
           float posX,
           float posY,
           std::vector<Script*> scripts);
    ~Entity();
    void runStartScripts();

    void setName(std::string name);
    std::string getName();

    void setHitboxSize(Vector2f size);
    void setHitboxSize(float width, float height);
    void setHitboxPosition(float x, float y);

    float getHitboxPositionX();
    void setHitboxPositionX(float value);

    float getHitboxPositionY();
    void setHitboxPositionY(float value);

    float getHitboxWidth();
    void setHitboxWidth(float value);

    float getHitboxHeight();
    void setHitboxHeight(float value);

    void update();
    Rectangle getHitbox();
    int getID();

    void addScript(Script* script);

    int getSpriteId();
    void setSpriteId(size_t spriteId);
};

#endif