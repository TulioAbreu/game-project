#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <fstream>
#include <set>
#include <string>

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
    std::string mFilePath;
    bool mFullLoad;

    void loadScripts();
    int getScriptIndexByName(std::string scriptName);
    void loadScene();
    void loadPrefabs();

public:
    Scene(std::string filePath, bool fullLoad);
    void load();
    void update();
};

#endif
