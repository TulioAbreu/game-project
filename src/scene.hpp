#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "entity-container.hpp"
#include "entity.hpp"

#include <fstream>
#include "log.hpp"
#include "../third-party/json.hpp"

class Scene {
    private:
    std::vector<Script*> mScripts;  // TODO: Why are scripts here? Switch it to Singleton?
    Entities* mRefEntities;

    void loadScripts() {
        std::fstream scriptsFile ("../data/behaviours/behaviours.json");
        if (!scriptsFile.is_open()) {
            LOG_ERROR("Scene/readSceneFile: Could not open behaviours/behaviours.json");
            return;
        }

        nlohmann::json scriptsJson;
        scriptsFile >> scriptsJson;

        for (auto script : scriptsJson) {
            const std::string filePath  =  script["path"];
            mScripts.push_back(new Script("../data/behaviours/" + filePath, script["name"]));
        }
    }

    void readSceneFile() {
        loadScripts();
        const int MONSTER_SCRIPT_ID = 0;
        const int PLAYER_SCRIPT_ID = 1;

        // This is just a placeholder
        mRefEntities->add(Entity(10, 10, 100, 100, {mScripts[MONSTER_SCRIPT_ID]}));
        mRefEntities->add(Entity(200, 200, 0, 0, {mScripts[MONSTER_SCRIPT_ID]}));
        mRefEntities->add(Entity(10, 10, -100, -100, {mScripts[PLAYER_SCRIPT_ID]}));
        mRefEntities->add(Entity(10, 10, 310, 0, {}));
        mRefEntities->add(Entity(50, 50, 200, 300, {}));

        for (size_t i = 0; i < mRefEntities->size(); ++i) {
            mRefEntities->at(i).runStartScripts();
        }
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
