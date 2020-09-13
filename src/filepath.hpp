#ifndef FILEPATH_HPP
#define FILEPATH_HPP

#include <string>

struct FilePath {
    std::string value;
};

FilePath Path(std::string relativeFilepath);

#endif
