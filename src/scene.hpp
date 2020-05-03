#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "entity-container.hpp"
#include "entity.hpp"

class Scene {
    private:
    std::vector<Script*> mScripts;
    Entities* mRefEntities;

    void readSceneFile() {
        mScripts.push_back(new Script("../data/monster.lua", "monster"));
        const int MONSTER_SCRIPT_ID = 0;

        mScripts.push_back(new Script("../data/player.lua", "player"));
        const int PLAYER_SCRIPT_ID = 1;

        // This is just a placeholder
        mRefEntities->add(Entity(10, 10, 100, 100, {mScripts[PLAYER_SCRIPT_ID]}));
        mRefEntities->add(Entity(200, 200, 0, 0, {mScripts[MONSTER_SCRIPT_ID]}));
        mRefEntities->add(Entity(10, 10, -100, -100, {mScripts[PLAYER_SCRIPT_ID]}));
        mRefEntities->add(Entity(10, 10, 310, 0, {}));
        mRefEntities->add(Entity(50, 50, 200, 300, {}));
    }
    public:
    Scene() {
        mRefEntities = (Entities*) Entities::getInstance();
        readSceneFile();
    }

    void update() {
        for (size_t i = 0; i < mRefEntities->size(); ++i) {
            mRefEntities->at(i).update();
        }
    }
};

#endif
