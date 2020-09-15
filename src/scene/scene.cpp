#include "scene.hpp"

static SpriteManager& gSpriteManager = *SpriteManager::getInstance();

Scene::Scene(std::string filePath, bool fullLoad) {
    mRefEntities = Entities::Container::getInstance();
    mFilePath = filePath;
    mFullLoad = fullLoad;

    if (fullLoad) {
        // TODO: load scene file first, get dependencies and load only what is necessary? After that, load by demand?
        loadScripts();
        loadPrefabs();
        loadScene();

        for (size_t i = 0; i < mRefEntities->size(); ++i) {
            mRefEntities->at(i).runStartScripts();
        }
    } else {
        loadPrefabs();
        loadScene();
    }
}

void Scene::update() {
    for (size_t i = 0; i < mRefEntities->size(); ++i) {
        mRefEntities->at(i).update();
    }
}

void Scene::loadScripts() {
    json scriptsJson;
    const FilePath DEFAULT_BEHAVIOURS_JSON_PATH = Path("data/behaviours/behaviours.json");
    bool loadedWithSuccess = JSON::load(DEFAULT_BEHAVIOURS_JSON_PATH.value, &scriptsJson);
    if (!loadedWithSuccess) {
        LOG_ERROR("Scene/loadScripts: Could not open behaviours/behaviours.json");
        return;
    }

    for (auto script : scriptsJson) {
        const std::string filePath  =  script["path"];
        mScriptsIndexMap[script["name"]] = mScripts.size();
        mScripts.push_back(new Script(Path("data/behaviours/").value + filePath, script["name"]));
    }
}

int Scene::getScriptIndexByName(std::string scriptName) {
    return mScriptsIndexMap.at(scriptName);
}

void Scene::loadScene() {
    json scene;
    bool loadedWithSuccess = JSON::load(mFilePath, &scene);
    if (!loadedWithSuccess) {
        LOG_ERROR("Scene/loadScene: Could not open scene file (" << mFilePath << ")");
        return;
    }

    json sceneEntries = scene["entries"];
    for (auto sceneEntry : sceneEntries) {
        const size_t entryPrefabId = sceneEntry["prefabId"];
        Entities::Prefab entryPrefab (mPrefabsMap[entryPrefabId]);
        
        Entity entity;
        if (sceneEntry["name"] != "") {
            entity.setName(sceneEntry["name"]);
        } else {
            entity.setName(entryPrefab.getName());
        }

        Vector2f size = entryPrefab.getDimensions();
        entity.setHitboxSize(size.x, size.y);
        entity.setHitboxPosition(sceneEntry["position"]["x"], sceneEntry["position"]["y"]);

        if (mFullLoad) {
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
        }

        const size_t generatedSpriteId = gSpriteManager.createSprite(entryPrefab.getSpriteId());
        entity.setSpriteId(generatedSpriteId);

        mRefEntities->add(entity);
    }
}

void Scene::loadPrefabs() {
    json entitiesIndexJson;
    bool loadedWithSuccess = JSON::load(Path("data/entities/entities.json").value, &entitiesIndexJson);
    if (!loadedWithSuccess) {
        LOG_ERROR("Scene/loadPrefabs: Could not open entities.json");
        return;
    }

    for (auto entity : entitiesIndexJson) {
        const int prefabId = entity["id"];
        const std::string filePath = entity["path"];
        mPrefabsMap[prefabId] = Entities::Prefab(Path("data/entities/" + filePath));
    }
}
