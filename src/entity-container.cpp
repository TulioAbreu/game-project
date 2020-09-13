#include "entity-container.hpp"
#include "utils/log/log.hpp"

size_t Entities::size() {
    return entities.size();
}

Entity Entities::at(int index) {
    return entities.at(index);
}

void Entities::add(Entity entity) {
    entities.push_back(entity);
}

bool Entities::remove(size_t index) {
    if (entities.empty()) {
        return false;
    } 
    if (index < 0 && index >= entities.size()) {
        return false;
    }

    entities.erase(entities.begin() + index);
    return true;
}

Entity* Entities::getEntityByID(int id) {
    for (auto& entity : entities) {
        if (entity.getID() == id) {
            return &entity;
        }
    }
    LOG_WARNING("Entities/getEntityByID: Returned nullptr reference after searcing for entity ID = " << id);
    return nullptr;
}

Entity* Entities::getEntityByName(std::string name) {
    for (auto& entity : entities) {
        if (entity.getName() == name) {
            return &entity;
        }
    }
    return nullptr;
}
