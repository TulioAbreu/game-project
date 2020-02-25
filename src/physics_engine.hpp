#ifndef PHYSICS_ENGINE_HPP
#define PHYSICS_ENGINE_HPP

#include <queue>
#include "entity.hpp" 
#include "entities.hpp"
#include "vector2.hpp"
#include "physics.hpp"

struct Collision {
    Entity* e1;
    Entity* e2;
};

class PhysicsEngine {
private:
    std::queue<Collision> collisions;

    inline void updateKinematics(Entities* entities, float deltaTime) {
        for (size_t i = 0; i < entities->size(); ++i) {
            Physics& physics = entities->at(i)->getPhysicsData();

            physics.speed = physics.speed + physics.acceleration;

            physics.hitbox->positionX += physics.speed.x;
            physics.hitbox->positionY += physics.speed.y;
        }
    }

    inline void queueCollisions(Entities* entities) {

    }

    inline void solveCollisions(Entities* entities) {

    }

public:
    void update(Entities* entities, float deltaTime) {
        updateKinematics(entities, deltaTime);
        queueCollisions(entities);
        solveCollisions(entities);
    }
};

#endif
