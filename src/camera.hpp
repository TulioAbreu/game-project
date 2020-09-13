#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "rectangle.hpp"
#include "utils/vector2/vector2.hpp"
#include "entity.hpp"
#include "singleton.hpp"
#include "sprite-manager.hpp"

class Camera: public Singleton<Camera> {
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
 
    void setGlobalPosition(const Vector2f position) {
        mGlobalPosition = position;
    }

    Vector2f getGlobalPosition() const {
        return mGlobalPosition;
    }

    void fixToEntity(Entity* entity) {
        mFixedEntityPtr = entity;
    }

    void setScale(float value) { 
        if (value < 0.01) { 
            mScale = 0.01; 
            return;
        }
        mScale = value; 
    }

    float getScale() { return mScale; }

    inline Rectangle getVisionRectangle(const Vector2f contextSize) const {
        // TODO: Scale must be applied here
        const Vector2f scaledContextSize = contextSize * (1.f/mScale);
        const Vector2f halfScaledContextSize = scaledContextSize * 0.5f;

        return {(float) scaledContextSize.x-2,
                (float) scaledContextSize.y-2,
                (mGlobalPosition.x-halfScaledContextSize.x)+1,
                (mGlobalPosition.y-halfScaledContextSize.y)+1};
    }

    bool isRectangleVisible(const Rectangle rect, const Vector2f contextSize) const {
        return getVisionRectangle(contextSize).intersects(rect);
    }

    inline Rectangle getRelativeRectangle(Rectangle rectangle, const Vector2f halfContextSize) {
        // TODO: Scale must be applied here
        if (mFixedEntityPtr) {
            mGlobalPosition = {mFixedEntityPtr->getHitboxPositionX(),
                               mFixedEntityPtr->getHitboxPositionY()};
            }

        return {rectangle.width*mScale, rectangle.height*mScale,
                rectangle.positionX*mScale-(mGlobalPosition.x*mScale-halfContextSize.x), rectangle.positionY*mScale-(mGlobalPosition.y*mScale-halfContextSize.y)};
    }
};


#endif
