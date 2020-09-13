#include "prefab.hpp"

Entities::Prefab::Prefab(FilePath filePath) {
    mFilepath = filePath.value;
    mName = "";
    loadFile();
}

void Entities::Prefab::loadFile() {
    std::fstream prefabFile (mFilepath);
    if (!prefabFile.is_open()) {
        LOG_ERROR("Prefab/loadFile: Could not open prefab file " << mFilepath);
        return;
    }

    json prefabJson;
    prefabFile >> prefabJson;

    mName = prefabJson["name"];
    mSpriteId = prefabJson["spriteId"];
    mDimensions = {
        prefabJson["dimensions"]["x"],
        prefabJson["dimensions"]["y"]
    };
    for (auto script : prefabJson["scripts"]) {
        mScriptNames.push_back(script);
    }
}

std::string Entities::Prefab::getName() const {
    return mName;
}

std::string Entities::Prefab::getFilepath() const {
    return mFilepath;
}

Vector2f Entities::Prefab::getDimensions() const {
    return mDimensions;
}

float Entities::Prefab::getDimensionsX() const {
    return mDimensions.x;
}

float Entities::Prefab::getDimensionsY() const {
    return mDimensions.y;
}

size_t Entities::Prefab::getSpriteId() const {
    return mSpriteId;
}

std::vector<std::string>& Entities::Prefab::getScriptNames() {
    return mScriptNames;
}
