#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "entity-container.hpp"
#include "entity.hpp"

class Scene {
    private:
    Entities mEntities;
    std::vector<Script*> mScripts;


    void readSceneFile() {
        mScripts.push_back(new Script("../data/monster.lua", "monster"));
        const int MONSTER_SCRIPT_ID = 0;

        mScripts.push_back(new Script("../data/player.lua", "player"));
        const int PLAYER_SCRIPT_ID = 0;

        // This is just a placeholder
        mEntities.add(Entity(200, 200, 0, 0, {mScripts[PLAYER_SCRIPT_ID]}));
        mEntities.add(Entity(10, 10, 100, 100, {mScripts[PLAYER_SCRIPT_ID]}));
        mEntities.add(Entity(10, 10, -100, -100, {mScripts[PLAYER_SCRIPT_ID]}));

        mEntities.add(Entity(10, 10, 310, 0, {}));
        mEntities.add(Entity(50, 50, 200, 300, {}));
    }
    public:
    Scene() {
        readSceneFile();
    }

    void update() {
        for (size_t i = 0; i < mEntities.size(); ++i) {
            mEntities.at(i).update();
        }
    }

    Entities& getEntities() {
        return mEntities;
    }
};

#endif
