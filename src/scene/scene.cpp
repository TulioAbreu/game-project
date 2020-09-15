#include "scene.hpp"
#include "reader/reader.hpp"

static SpriteManager& gSpriteManager = *SpriteManager::getInstance();

Scene::Scene(FilePath filePath, bool fullLoad) {
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
    SceneFile sceneFile;
    bool loadedWithSuccess = readSceneFromFile(mFilePath, sceneFile);
    if (!loadedWithSuccess) {
        LOG_ERROR("Scene/loadScene: Could not open scene file (" << mFilePath.value << ")");
        return;
    }

    for (auto sceneEntry : sceneFile.entries) {
        const size_t entryPrefabId = sceneEntry.prefabId;
        Entity entity;
        Entities::Prefab entryPrefab (mPrefabsMap[entryPrefabId]);
        entity.setName((sceneEntry.name != "") ? sceneEntry.name : entryPrefab.getName());
        entity.setHitboxSize(entryPrefab.getDimensions());
        entity.setHitboxPosition(sceneEntry.position.x, sceneEntry.position.y);

        if (mFullLoad) {
            std::set<std::string> scriptNamesSet (sceneEntry.scripts.begin(), sceneEntry.scripts.end());

            const auto scriptsFromEntityPrefab = entryPrefab.getScriptNames();
            scriptNamesSet.insert(scriptsFromEntityPrefab.begin(), scriptsFromEntityPrefab.end());

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
