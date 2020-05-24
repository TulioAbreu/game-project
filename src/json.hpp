#ifndef JSON_HPP
#define JSON_HPP

#include "../third-party/json.hpp"
#include <fstream>

using json = nlohmann::json;

namespace JSON {
    bool load(std::string filePath, json* jsonObject);
};

#endif
