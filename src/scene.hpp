#ifndef SCENE_HPP
#define SCENE_HPP

#include "entity-container.hpp"
#include "entity.hpp"
#include "log.hpp"

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        // elems.push_back(item);
        elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
    }
    return elems;
}

class Scene {
    private:
    Entities mEntities;

    std::string getFileContent(std::string filepath) {
        std::ifstream file (filepath);
        if (!file.is_open()) {
            std::cout << ERROR_PREFIX << "Could not open file => " << filepath << std::endl;
            return "";
        }
        std::string fileContent((std::istreambuf_iterator<char>(file)),
                                 std::istreambuf_iterator<char>());
        file.close();
        return fileContent;
    }

    Vector2f ParseVector2f(std::string valueStr) {
        auto values = split(valueStr, ' ');
        return {std::stof(values[0]), std::stof(values[1])};
    }

    Vector2f ParseSize(std::string valueStr) {
        return ParseVector2f(valueStr);
    }

    Vector2f ParsePosition(std::string valueStr) {
        return ParseVector2f(valueStr);
    }

    void readSceneFile(std::string filepath) {
        std::string sceneStr = getFileContent(filepath);
        if (sceneStr == "") {
            return;
        }

        auto sceneStrVec = split(sceneStr, '\n');
        for (auto sceneStrElement : sceneStrVec) {
            auto nameAttributesVec = split(sceneStrElement, '>');
            if (nameAttributesVec.size() != 2) {
                continue;
            }

            const std::string elementName = nameAttributesVec[0];
            const std::string allAttributesStr = nameAttributesVec[1];

            Vector2f size, position;

            auto attributesVec = split(allAttributesStr, ';');
            for (auto attribute : attributesVec) {
                auto attributeValueVec = split(attribute, ':');
                
                const std::string attributeTitleStr = attributeValueVec[0];
                const std::string attributeValueStr = attributeValueVec[1];

                if (attributeTitleStr == "size") {
                    size = ParseSize(attributeValueStr);
                }
                else if (attributeTitleStr == "position") {
                    position = ParsePosition(attributeValueStr);
                }
            }
            mEntities.add(Entity(size.x, size.y, position.x, position.y));
        }
    }
    public:
    Scene(std::string filepath) {
        readSceneFile(filepath);
    }

    void update() {
        for (size_t i = 0; i < mEntities.size(); ++i) {
            mEntities.at(i).update();
        }
    }

    Entities& getEntities() {
        return mEntities;
    }
};

#endif
