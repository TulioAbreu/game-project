#ifndef ENTITY_CONTAINER_HPP
#define ENTITY_CONTAINER_HPP

#include <vector>
#include "../../entity.hpp"
#include "../../singleton.hpp"

namespace Entities {
class Container: public Singleton<Container> {
private:
    // TODO: implement a more sophisticated data structure 
    std::vector<Entity> entities;
public:
    Container() = default;
    size_t size();
    Entity at(int index);
    void add(Entity entity);
    bool remove(size_t index);
    Entity* getEntityByID(int id);
    Entity* getEntityByName(std::string name);
};
};

#endif