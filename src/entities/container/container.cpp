#include "container.hpp"
#include "../../utils/log/log.hpp"

size_t Entities::Container::size() {
    return entities.size();
}

Entity Entities::Container::at(int index) {
    return entities.at(index);
}

void Entities::Container::add(Entity entity) {
    entities.push_back(entity);
}

bool Entities::Container::remove(size_t index) {
    if (entities.empty()) {
        return false;
    } 
    if (index < 0 && index >= entities.size()) {
        return false;
    }

    entities.erase(entities.begin() + index);
    return true;
}

Entity* Entities::Container::getEntityByID(int id) {
    for (auto& entity : entities) {
        if (entity.getID() == id) {
            return &entity;
        }
    }
    LOG_WARNING("Entities/getEntityByID: Returned nullptr reference after searcing for entity ID = " << id);
    return nullptr;
}

Entity* Entities::Container::getEntityByName(std::string name) {
    for (auto& entity : entities) {
        if (entity.getName() == name) {
            return &entity;
        }
    }
    return nullptr;
}
