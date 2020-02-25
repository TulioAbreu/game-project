#ifndef PHYSICS_ENGINE_HPP
#define PHYSICS_ENGINE_HPP

#include <queue>
#include "physics.hpp"
#include "entity.hpp" 
#include "entities.hpp"
#include "vector2.hpp"


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
        // TODO: O(n²)! It requires another structure.
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

    enum Direction {NONE = 0, NORTH, EAST, SOUTH, WEST};
    Direction getCollisionDirection(Physics* obj1, Physics* obj2) {
        return NONE;
    }

    inline void solveKNCollision(Physics* kinematic, Physics* nonKinematic) {
        // descobrir de onde veio a colisão
        Direction dir = getCollisionDirection(kinematic, nonKinematic);

        if (dir == NORTH || dir == SOUTH) {
            nonKinematic->speed.y = 0;
        }
        else if (dir == WEST || dir == EAST) {
            nonKinematic->speed.x = 0;
        }
        else {
            nonKinematic->speed.x = 0;
            nonKinematic->speed.y = 0;
        }

        // "expurgar o objeto"

    }

    inline void solveCollisions() {
        Physics* e1Physics = nullptr;
        Physics* e2Physics = nullptr;
        for (size_t i = 0; i < collisions.size(); ++i) {
            const Collision currCollision = collisions.front();
            collisions.pop();

            e1Physics = &currCollision.e1->getPhysicsData();
            e2Physics = &currCollision.e2->getPhysicsData();

            if (e1Physics->isKinematic && e2Physics->isKinematic) {
                continue;
            }
            if (e1Physics->isKinematic) {
                solveKNCollision(e1Physics, e2Physics);
            } 
            else if (e2Physics->isKinematic) {
                solveKNCollision(e2Physics, e1Physics);
            }
            else {  // No kinematic entity 

            }

            currCollision.e1->onCollision(currCollision);
            currCollision.e2->onCollision(currCollision);
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
