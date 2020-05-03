#ifndef ENTITY_CONTAINER_HPP
#define ENTITY_CONTAINER_HPP

#include <vector>
#include "entity.hpp"
#include "singleton.hpp"

class Entities: public Singleton<Entities> {
private:
    // TODO: implement a more sophisticated data structure 
    std::vector<Entity> entities;

public:
    Entities() = default;

    size_t size() {
        return entities.size();
    }

    Entity at(int index) {
        return entities.at(index);
    }

    void add(Entity entity) {
        entities.push_back(entity);
    }

    bool remove(size_t index) {
        if (entities.empty()) {
            return false;
        } 
        if (index < 0 && index >= entities.size()) {
            return false;
        }

        entities.erase(entities.begin() + index);
        return true;
    }

    Entity* getEntityByID(int id) {
        for (auto& entity : entities) {
            if (entity.getID() == id) {
                return &entity;
            }
        }
        return nullptr;
    }
};

#endif