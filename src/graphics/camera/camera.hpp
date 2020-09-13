#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../../utils/vector2/vector2.hpp"
#include "../../rectangle.hpp"
#include "../../entity.hpp"
#include "../../singleton.hpp"
#include "../../sprite-manager.hpp"

namespace Graphics {
class Camera: public Singleton<Camera> {
    float mScale;
    Vector2f mGlobalPosition;
    Vector2f mWindowCenter;
    Entity* mFixedEntityPtr;

    Vector2f getScaledSize(const Rectangle rectangle);

public:
    Camera();
    void setGlobalPosition(const Vector2f position);
    Vector2f getGlobalPosition() const;
    void fixToEntity(Entity* entity);
    void setScale(float value);
    float getScale();
    Rectangle getVisionRectangle(const Vector2f contextSize) const;
    bool isRectangleVisible(const Rectangle rect, const Vector2f contextSize) const;
    Rectangle getRelativeRectangle(Rectangle rectangle, const Vector2f halfContextSize);
};
}


#endif
