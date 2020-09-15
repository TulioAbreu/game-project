#include "reader.hpp"

SceneFile readSceneFromFile(FilePath filePath) {
    json sceneJson;
    bool success = JSON::load(filePath.value, &sceneJson);
    SceneFile sceneFile;

    for (auto fileEntry : sceneJson["entries"]) {
        Entry newEntry;
        newEntry.name = fileEntry["name"];
        newEntry.prefabId = fileEntry["prefabId"];
        newEntry.position = {
            fileEntry["position"]["x"],
            fileEntry["position"]["y"]
        };

        for (auto fileEntryScript : fileEntry["scripts"]) {
            newEntry.scripts.push_back(fileEntryScript);
        }
        sceneFile.entries.push_back(newEntry);
    }

    return sceneFile;
}
