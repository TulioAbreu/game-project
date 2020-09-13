#include "camera.hpp"

Graphics::Camera::Camera() {
    mScale = 1;
    mFixedEntityPtr = nullptr;
    mGlobalPosition = {0, 0};
    mWindowCenter = {0, 0};
}

Vector2f Graphics::Camera::getScaledSize(const Rectangle rectangle) {
    return {rectangle.width * mScale, rectangle.height * mScale};
}

void Graphics::Camera::setGlobalPosition(const Vector2f position) {
    mGlobalPosition = position;
}

Vector2f Graphics::Camera::getGlobalPosition() const {
    return mGlobalPosition;
}

void Graphics::Camera::fixToEntity(Entity* entity) {
    mFixedEntityPtr = entity;
}

void Graphics::Camera::setScale(float value) { 
    if (value < 0.01) { 
        mScale = 0.01; 
        return;
    }
    mScale = value; 
}

float Graphics::Camera::getScale() {
    return mScale;
}

Rectangle Graphics::Camera::getVisionRectangle(const Vector2f contextSize) const {
    // TODO: Scale must be applied here
    const Vector2f scaledContextSize = contextSize * (1.f/mScale);
    const Vector2f halfScaledContextSize = scaledContextSize * 0.5f;

    return {(float) scaledContextSize.x-2,
            (float) scaledContextSize.y-2,
            (mGlobalPosition.x-halfScaledContextSize.x)+1,
            (mGlobalPosition.y-halfScaledContextSize.y)+1};
}

bool Graphics::Camera::isRectangleVisible(const Rectangle rect, const Vector2f contextSize) const {
    return getVisionRectangle(contextSize).intersects(rect);
}

Rectangle Graphics::Camera::getRelativeRectangle(Rectangle rectangle, const Vector2f halfContextSize) {
    // TODO: Scale must be applied here
    if (mFixedEntityPtr) {
        mGlobalPosition = {mFixedEntityPtr->getHitboxPositionX(),
                            mFixedEntityPtr->getHitboxPositionY()};
        }

    return {rectangle.width*mScale, rectangle.height*mScale,
            rectangle.positionX*mScale-(mGlobalPosition.x*mScale-halfContextSize.x), rectangle.positionY*mScale-(mGlobalPosition.y*mScale-halfContextSize.y)};
}
