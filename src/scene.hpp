#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <fstream>
#include <set>
#include <string>
#include <map>

#include "entities/container/container.hpp"
#include "entity.hpp"
#include "utils/log/log.hpp"
#include "entities/prefab/prefab.hpp"
#include "json.hpp"
#include "sprite-manager.hpp"

class Scene {
    private:
    std::vector<Script*> mScripts;  // TODO: Why are scripts here? Switch it to Singleton?
    std::map<std::string, size_t> mScriptsIndexMap;
    std::map<size_t, Entities::Prefab> mPrefabsMap;
    Entities::Container* mRefEntities;
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
