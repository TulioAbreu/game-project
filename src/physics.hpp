#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "vector2.hpp"
#include "rectangle.hpp"

struct Entity;

struct Physics {
    bool isKinematic;
    Vector2f acceleration;
    Vector2f speed;
    Rectangle* hitbox;
};

struct Collision {
    Entity* e1;
    Entity* e2;
};

#endif