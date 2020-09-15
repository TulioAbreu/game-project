#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <fstream>
#include <set>
#include <string>
#include <map>

#include "../json.hpp"
#include "../entity.hpp"
#include "../entities/container/container.hpp"
#include "../entities/prefab/prefab.hpp"
#include "../sprite-manager.hpp"
#include "../utils/log/log.hpp"
#include "../utils/filepath/filepath.hpp"

class Scene {
    private:
    std::vector<Script*> mScripts;  // TODO: Why are scripts here? Switch it to Singleton?
    std::map<std::string, size_t> mScriptsIndexMap;
    std::map<size_t, Entities::Prefab> mPrefabsMap;
    Entities::Container* mRefEntities;
    FilePath mFilePath;
    bool mFullLoad;

    void loadScripts();
    int getScriptIndexByName(std::string scriptName);
    void loadScene();
    void loadPrefabs();

public:
    Scene(FilePath filePath, bool fullLoad);
    void load();
    void update();
};

#endif
