#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <algorithm>

struct Rectangle {
    float width, height;
    float positionX, positionY;

    bool intersects(const Rectangle& other) const;
};

bool intersects(const Rectangle& a, const Rectangle& b);


#endif