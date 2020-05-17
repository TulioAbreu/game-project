#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <fstream>
#include <set>

#include "entity-container.hpp"
#include "entity.hpp"
#include "log.hpp"
#include "filepath.hpp"
#include "prefab.hpp"
#include "json.hpp"

class Scene {
    private:
    std::vector<Script*> mScripts;  // TODO: Why are scripts here? Switch it to Singleton?
    std::map<size_t, Prefab> mPrefabsMap;
    Entities* mRefEntities;

    void loadScripts() {
        std::fstream scriptsFile (Path("data/behaviours/behaviours.json"));
        if (!scriptsFile.is_open()) {
            LOG_ERROR("Scene/loadScripts: Could not open behaviours/behaviours.json");
            return;
        }

        json scriptsJson;
        scriptsFile >> scriptsJson;

        for (auto script : scriptsJson) {
            const std::string filePath  =  script["path"];
            mScripts.push_back(new Script(Path("data/behaviours/") + filePath, script["name"]));
        }
    }

    int getScriptIndexByName(std::string scriptName) {
        // TODO: Implement with Map type structure
        for (size_t i = 0; i < mScripts.size(); ++i) {
            if (mScripts[i]->getName() == scriptName) {
                return i;
            }
        }
        return -1;
    }

    void loadScene() {
        std::fstream sceneFile ("../data/scenes/scene_01.json");
        if (!sceneFile.is_open()) {
            LOG_ERROR("Scene/loadScene: Could not open scene file");
            return;
        }

        json scene;
        sceneFile >> scene;

        json sceneEntries = scene["entries"];
        for (auto sceneEntry : sceneEntries) {
            const size_t entryPrefabId = sceneEntry["prefabId"];
            Prefab entryPrefab (mPrefabsMap[entryPrefabId]);
            
            Entity entity;
            if (sceneEntry["name"] != "") {
                entity.setName(sceneEntry["name"]);
            } else {
                entity.setName(entryPrefab.getName());
            }

            Vector2f size = entryPrefab.getDimensions();
            entity.setHitboxSize(size.x, size.y);
            entity.setHitboxPosition(sceneEntry["position"]["x"], sceneEntry["position"]["y"]);

            std::set<std::string> scriptNamesSet;
            for (auto scriptName : entryPrefab.getScriptNames()) {
                scriptNamesSet.insert(scriptName);
            }
            for (auto scriptNameJson : sceneEntry["scripts"]) {
                const std::string scriptName = scriptNameJson;
                scriptNamesSet.insert(scriptName);
            }

            for (auto scriptName : scriptNamesSet) {
                entity.addScript(mScripts[getScriptIndexByName(scriptName)]);
            }

            mRefEntities->add(entity);
        }
    }

    void loadPrefabs() {
        std::fstream entitiesIndexFile (Path("data/entities/entities.json"));
        if (!entitiesIndexFile.is_open()) {
            LOG_ERROR("Scene/loadPrefabs: Could not open entities.json");
            return;
        }

        json entitiesIndexJson;
        entitiesIndexFile >> entitiesIndexJson;

        for (auto entity : entitiesIndexJson) {
            const int prefabId = entity["id"];
            const std::string filePath = entity["path"];
            mPrefabsMap[prefabId] = Prefab(Path("data/entities/" + filePath));
        }
    }

    void readSceneFile() {
        loadScripts();
        loadPrefabs();
        loadScene();

        for (size_t i = 0; i < mRefEntities->size(); ++i) {
            mRefEntities->at(i).runStartScripts();
        }
    }

public:
    Scene() {
        mRefEntities = Entities::getInstance();
        readSceneFile();
    }

    void update() {
        for (size_t i = 0; i < mRefEntities->size(); ++i) {
            mRefEntities->at(i).update();
        }
    }
};

#endif
