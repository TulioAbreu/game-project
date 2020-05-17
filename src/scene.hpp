#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <fstream>
#include <set>

#include "entity-container.hpp"
#include "entity.hpp"
#include "log.hpp"
#include "prefab.hpp"
#include "json.hpp"
#include "sprite-manager.hpp"

class Scene {
    private:
    std::vector<Script*> mScripts;  // TODO: Why are scripts here? Switch it to Singleton?
    std::map<size_t, Prefab> mPrefabsMap;
    Entities* mRefEntities;

    void loadScripts();
    int getScriptIndexByName(std::string scriptName);
    void loadScene();
    void loadPrefabs();
    void readSceneFile();

public:
    Scene();
    void update();
};

#endif
