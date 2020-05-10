#ifndef FILEPATH_HPP
#define FILEPATH_HPP

#include <string>

const std::string FILEPATH_ROOT ("../");

std::string Path(std::string relativeFilepath) {
    return FILEPATH_ROOT + relativeFilepath;
}

#endif
