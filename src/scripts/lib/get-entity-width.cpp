#include "../../entities/container/container.hpp"
#include "../core.hpp"
#include "../library.hpp"

#define EXPECTED_ARGS_LEN 1

static auto gEntities = Entities::Container::getInstance();

int lua_getEntityWidth(lua_State* L)
{
    if (!hasCorrectArgsLength(L, EXPECTED_ARGS_LEN)) {
        return 0;
    }

    const int entityId = lua_tonumber(L, 1);

    auto entity = gEntities->getEntityByID(entityId);
    if (!entity) {
        return 0;
    }

    const int entityWidth = entity->getHitboxWidth();
    lua_pushnumber(L, entityWidth);

    return 1;
}
