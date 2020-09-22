#include "filepath.hpp"

const std::string FILEPATH_ROOT ("../");

FilePath Path(std::string relativeFilePath) {
    return FilePath(relativeFilePath);
}

FilePath::FilePath(std::string relativeFilepath) {
    value = FILEPATH_ROOT + relativeFilepath;
}
