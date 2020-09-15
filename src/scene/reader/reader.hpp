#ifndef READER_HPP
#define READER_HPP

#include <vector>
#include <string>
#include "../../utils/filepath/filepath.hpp"
#include "../../utils/vector2/vector2.hpp"
#include "../../json.hpp"

struct Entry {
    std::string name;
    int prefabId;
    Vector2i position;
    std::vector<std::string> scripts;
};

struct SceneFile {
    std::vector<Entry> entries;
};

bool readSceneFromFile(FilePath filePath, SceneFile& sceneFile);

#endif
