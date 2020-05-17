#ifndef PREFAB_HPP
#define PREFAB_HPP

#include <fstream>
#include <string>
#include <vector>
#include "json.hpp"
#include "log.hpp"
#include "vector2.hpp"

class Prefab {
private:
    std::string mName;
    std::string mFilepath;
    Vector2f mDimensions;
    size_t mSpriteId;
    std::vector<std::string> mScriptNames;

public:
    Prefab() = default;
    Prefab(std::string filepath) {
        mFilepath = filepath;
        mName = "";
        loadFile();
    }

    void loadFile() {
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

    std::string getName() {
        return mName;
    }

    std::string getFilepath() {
        return mFilepath;
    }

    Vector2f getDimensions() {
        return mDimensions;
    }

    float getDimensionsX() {
        return mDimensions.x;
    }

    float getDimensionsY() {
        return mDimensions.y;
    }

    size_t getSpriteId() {
        return mSpriteId;
    }

    std::vector<std::string>& getScriptNames() {
        return mScriptNames;
    }
};

#endif