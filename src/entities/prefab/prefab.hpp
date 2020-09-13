#ifndef PREFAB_HPP
#define PREFAB_HPP

#include <fstream>
#include <string>
#include <vector>
#include "../../json.hpp"
#include "../../utils/log/log.hpp"
#include "../../utils/filepath/filepath.hpp"
#include "../../utils/vector2/vector2.hpp"

namespace Entities {
class Prefab {
private:
    std::string mName;
    std::string mFilepath;
    Vector2f mDimensions;
    size_t mSpriteId;
    std::vector<std::string> mScriptNames;

public:
    Prefab() = default;
    Prefab(FilePath filePath);
    void loadFile();
    std::string getName() const;
    std::string getFilepath() const;
    Vector2f getDimensions() const;
    float getDimensionsX() const;
    float getDimensionsY() const;
    size_t getSpriteId() const;
    std::vector<std::string>& getScriptNames();
};
};

#endif