#ifndef SCENE_HPP
#define SCENE_HPP

#include "entities.hpp"

class Scene {
private:
    Entities mEntities;

    void readSceneFile() {
        // This is just a placeholder
        mEntities.add(Entity(200, 200, 0, 0));
        mEntities.add(Entity(10, 10, 100, 100));
        mEntities.add(Entity(10, 10, -100, -100));

        mEntities.add(Entity(10, 10, 310, 0));
        mEntities.add(Entity(50, 50, 200, 300));
    }
public:
    Scene() {
        readSceneFile();
    }

    void update() {
        for (int i = 0; i < mEntities.size(); ++i) {
            mEntities.at(i).update();
        }
    }

    Entities& getEntities() {
        return mEntities;
    }
};

#endif