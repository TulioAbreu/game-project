#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <algorithm>
#include "vector2.hpp"

struct Rectangle {

    float width, height;
    Vector2f position;


    bool intersects(const Rectangle& other) const {
        float x_overlap = std::max(0.f, std::min(position.x+width, other.position.x+other.width) - std::max(position.x, other.position.x));
        float y_overlap = std::max(0.f, std::min(position.y+height, other.position.y+height) - std::max(position.y, other.position.y));
        float overlapArea = x_overlap * y_overlap;

        return (overlapArea > 0);
    }
};

#endif