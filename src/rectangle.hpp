#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <algorithm>

struct Rectangle {
    float width, height;
    float positionX, positionY;

    bool intersects(const Rectangle& other) const {
        float x_overlap = std::max(0.f, std::min(positionX+width, other.positionX+other.width) - std::max(positionX, other.positionX));
        float y_overlap = std::max(0.f, std::min(positionY+height, other.positionY+height) - std::max(positionY, other.positionY));
        float overlapArea = x_overlap * y_overlap;

        return (overlapArea > 0);
    }
};

#endif