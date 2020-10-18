#include "../../entities/container/container.hpp"
#include "../core.hpp"
#include "../library.hpp"

#define EXPECTED_ARGS_LEN 2

static auto gEntities = Entities::Container::getInstance();

int lua_setEntityWidth(lua_State* L)
{
    if (!hasCorrectArgsLength(L, EXPECTED_ARGS_LEN)) {
        return 0;
    }

    const int entityId = lua_tonumber(L, 1);
    const int width = lua_tonumber(L, 2);

    auto entity = gEntities->getEntityByID(entityId);
    if (!entity) {
        return 0;
    }

    entity->setHitboxWidth(width);

    return 1;
}
