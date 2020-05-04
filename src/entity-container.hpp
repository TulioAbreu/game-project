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
    size_t size();
    Entity at(int index);
    void add(Entity entity);
    bool remove(size_t index);
    Entity* getEntityByID(int id);
};

#endif