#include "rectangle.hpp"

bool Rectangle::intersects(const Rectangle& other) const {
    float x_overlap = std::max(0.f, std::min(positionX+width, other.positionX+other.width) - std::max(positionX, other.positionX));
    float y_overlap = std::max(0.f, std::min(positionY+height, other.positionY+height) - std::max(positionY, other.positionY));
    float overlapArea = x_overlap * y_overlap;

    return (overlapArea > 0);
}


bool intersects(const Rectangle& a, const Rectangle& b) {
    float x_overlap = std::max(0.f, std::min(a.positionX+a.width, b.positionX+b.width) - std::max(a.positionX, b.positionX));
    float y_overlap = std::max(0.f, std::min(a.positionY+a.height, b.positionY+a.height) - std::max(a.positionY, b.positionY));
    float overlapArea = x_overlap * y_overlap;

    return (overlapArea > 0);
}
