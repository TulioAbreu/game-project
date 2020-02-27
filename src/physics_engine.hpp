#ifndef PHYSICS_ENGINE_HPP
#define PHYSICS_ENGINE_HPP

#include <queue>
#include <map>
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

            physics.speed = physics.speed + physics.acceleration * deltaTime;

            physics.hitbox->position = physics.hitbox->position + physics.speed;
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
        // TODO: Implement this
        return NORTH;
    }

    inline void restartDirectionSpeed(Physics* nonKinematic, Direction* direction) {
        if (*direction == NORTH || *direction == SOUTH) {
            nonKinematic->speed.y = 0;
        }
        else if (*direction == WEST || *direction == EAST) {
            nonKinematic->speed.x = 0;
        }
        else {
            nonKinematic->speed.x = 0;
            nonKinematic->speed.y = 0;
        }
    }

    inline void solveKNCollision(Physics* kinematic, Physics* nonKinematic) {
        Direction dir = getCollisionDirection(kinematic, nonKinematic);
        restartDirectionSpeed(nonKinematic, &dir);

        switch (dir) {
            case NORTH: {
                std::cout << " Before = " << kinematic->hitbox->position.y << std::endl;
                kinematic->hitbox->position.y -= (kinematic->hitbox->position.y + kinematic->hitbox->size.y) - nonKinematic->hitbox->position.y;
                std::cout << " After = " << kinematic->hitbox->position.y << std::endl;
            } break; 
            case EAST: {
                // TODO: Implement this
            } break; 
            case SOUTH: {
                // TODO: Implement this
            } break; 
            case WEST: {
                // TODO: Implement this
            } break;
        }
    }

    inline void solveCollisions() {
        if (collisions.empty()) {
            return;
        }

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
