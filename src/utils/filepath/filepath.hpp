#ifndef FILEPATH_HPP
#define FILEPATH_HPP

#include <string>

struct FilePath {
    std::string value;

    FilePath() = default;
    FilePath(std::string relativeFilepath);
};

FilePath Path(std::string relativeFilepath);

#endif
