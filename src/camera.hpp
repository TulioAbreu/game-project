#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "rectangle.hpp"
#include "vector2.hpp"
#include "entity.hpp"

class Camera {
    float mScale;
    Vector2f mGlobalPosition;
    Vector2f mWindowCenter;
    Entity* mFixedEntityPtr;

    private:
    Vector2f getScaledSize(const Rectangle rectangle) {
        return {rectangle.width*mScale, rectangle.height*mScale};
    }

    public:
    Camera() {
        mScale = 1;
        mFixedEntityPtr = nullptr;
        mGlobalPosition = {0, 0};
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

    bool isRectangleVisible(const Rectangle rect, const Vector2i contextSize) const {
        // TODO: Scale must be applied here
        const float halfContextWidth = contextSize.x / 2.f;
        const float halfContextHeight = contextSize.y / 2.f;

        const Rectangle visionRect = {
            contextSize.x,
            contextSize.y,
            mGlobalPosition.x-halfContextWidth,
            mGlobalPosition.y-halfContextHeight};

        return visionRect.intersects(rect);
    }

    inline Rectangle getRelativeRectangle(Rectangle rectangle, const Vector2i halfContextSize) {
        // TODO: Scale must be applied here
        return {rectangle.width*mScale, rectangle.height*mScale,
                rectangle.positionX-(mGlobalPosition.x-halfContextSize.x), rectangle.positionY-(mGlobalPosition.y-halfContextSize.y)};
    }
};


#endif
