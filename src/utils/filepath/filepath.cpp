#include "filepath.hpp"

#define FILEPATH_ROOT std::string("../")

FilePath Path(std::string relativeFilePath) {
    return FilePath(relativeFilePath);
}

FilePath::FilePath(std::string relativeFilepath) {
    value = FILEPATH_ROOT + relativeFilepath;
}
