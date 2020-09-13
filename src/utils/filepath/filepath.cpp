#include "filepath.hpp"

FilePath Path(std::string relativeFilepath) {
    const std::string FILEPATH_ROOT ("../");
    return {FILEPATH_ROOT + relativeFilepath};
}
