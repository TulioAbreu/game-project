#include "scene.hpp"
#include "filepath.hpp"

static SpriteManagder& gSpriteManager = *SpriteManager::getInstance();


Scene::Scene(std::string filePath, bool fullLoad) {
    mRefEntities = Entities::getInstance();
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
    bool loadedWithSuccess = JSON::load(Path("data/behaviours/behaviours.json"), &scriptsJson);
    if (!loadedWithSuccess) {
        LOG_ERROR("Scene/loadScripts: Could not open behaviours/behaviours.json");
        return;
    }

    for (auto script : scriptsJson) {
        const std::string filePath  =  script["path"];
        mScripts.push_back(new Script(Path("data/behaviours/") + filePath, script["name"]));
    }
}

int Scene::getScriptIndexByName(std::string scriptName) {
    // TODO: Implement with Map type structure
    for (size_t i = 0; i < mScripts.size(); ++i) {
        if (mScripts[i]->getName() == scriptName) {
            return i;
        }
    }
    return -1;
}

void Scene::loadScene() {
    json scene;
    bool loadedWithSuccess = JSON::load(mFilePath, &scene);
    if (!loadedWithSuccess) {
        LOG_ERROR("Scene/loadScene: Could not open scene file");
        return;
    }

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

        const size_t generatedSpriteId = gSpriteManager.createSprite(entryPrefab.getSpriteId());
        entity.setSpriteId(generatedSpriteId);

        mRefEntities->add(entity);
    }
}

void Scene::loadPrefabs() {
    json entitiesIndexJson;
    bool loadedWithSuccess = JSON::load(Path("data/entities/entities.json"), &entitiesIndexJson);
    if (!loadedWithSuccess) {
        LOG_ERROR("Scene/loadPrefabs: Could not open entities.json");
        return;
    }

    for (auto entity : entitiesIndexJson) {
        const int prefabId = entity["id"];
        const std::string filePath = entity["path"];
        mPrefabsMap[prefabId] = Prefab(Path("data/entities/" + filePath));
    }
}
