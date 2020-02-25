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
        for (size_t i = 0; i < entities->size(); ++i) {
            for (size_t j = 0; j < entities->size(); ++j) {
                if (i == j) { continue; }
                
                Entity* e1Ptr = entities->at(i);
                Entity* e2Ptr = entities->at(j);

                if (e1Ptr->getHitbox().intersects(e2Ptr->getHitbox())) {
                    collisions.push({e1Ptr, e2Ptr});
                }
            }
        }
    }

    inline void solveCollisions() {
        for (size_t i = 0; i < collisions.size(); ++i) {
            const Collision currentCollision = collisions.front();
            collisions.pop();
        }
    }

public:
    void update(Entities* entities, float deltaTime) {
        updateKinematics(entities, deltaTime);
        queueCollisions(entities);
        solveCollisions();
    }
};

#endif
