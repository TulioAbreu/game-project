#ifndef SCENE_HPP
#define SCENE_HPP

#include "entities.hpp"

class Scene {
private:
    Entities mEntities;

    void readSceneFile() {
        // This is just a placeholder
        Entity* newEntity = nullptr;
 
        newEntity = new Entity(200, 200, 0, 0);
        newEntity->setKinematic(false);
        mEntities.add(newEntity);

        newEntity = new Entity(10, 10, 100, 100);
        newEntity->getPhysicsData().acceleration = {0.5, 0.5};
        mEntities.add(newEntity);
    }
public:
    Scene() {
        readSceneFile();
    }

    void update() {
        for (int i = 0; i < mEntities.size(); ++i) {
            mEntities.at(i)->update();
        }
    }

    Entities* getEntities() {
        return &mEntities;
    }
};

#endif