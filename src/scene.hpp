#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <fstream>

#include "entity-container.hpp"
#include "entity.hpp"
#include "log.hpp"
#include "filepath.hpp"

#include "json.hpp"

class Scene {
    private:
    std::vector<Script*> mScripts;  // TODO: Why are scripts here? Switch it to Singleton?
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
            std::vector<Script*> scripts;
            for (auto entryScript : sceneEntry["scripts"]) {
                scripts.push_back(mScripts[getScriptIndexByName(entryScript)]);
            }

            mRefEntities->add(Entity(
                sceneEntry["dimensions"]["x"],
                sceneEntry["dimensions"]["y"],
                sceneEntry["position"]["x"],
                sceneEntry["position"]["y"],
                scripts
            ));
        }
    }

    void readSceneFile() {
        loadScripts();
        loadScene();

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
