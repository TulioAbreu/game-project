#include "json.hpp"

bool JSON::load(std::string filePath, json* jsonObject)
{
    if (!jsonObject) {
        return false;
    }

    std::fstream file(filePath);
    if (!file.is_open()) {
        return false;
    }

    file >> *jsonObject;
    file.close();
    return true;
}
