#ifndef ENTITIES_HPP
#define ENTITIES_HPP
#include <vector>
#include "entity.hpp"

class Entities {
    // TODO: implement a more sophisticated data structure 
    private:
    std::vector<Entity> entities;

    public:
    size_t size() {
        return entities.size();
    }

    Entity at(int index) {
        return entities.at(index);
    }

    void add(Entity entity) {
        entities.push_back(entity);
    }

    bool remove(int index) {
        if (entities.empty()) {
            return false;
        } 
        if (index < 0 && index >= entities.size()) {
            return false;
        }

        entities.erase(entities.begin() + index);
        return true;
    }
};

#endif