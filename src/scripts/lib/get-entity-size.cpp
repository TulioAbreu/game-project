#include "../../entities/container/container.hpp"
#include "../core.hpp"
#include "../library.hpp"

#define EXPECTED_ARGS_LEN 1

static auto gEntities = Entities::Container::getInstance();

int lua_getEntitySize(lua_State* L)
{
    if (!hasCorrectArgsLength(L, EXPECTED_ARGS_LEN)) {
        return 0;
    }

    if (!hasCorrectArgsLength(L, EXPECTED_ARGS_LEN)) {
        return 0;
    }
    const int entityId = lua_tonumber(L, 1);

    auto entity = gEntities->getEntityByID(entityId);
    if (!entity) {
        return 0;
    }

    lua_newtable(L);

    lua_pushstring(L, "x");
    lua_pushnumber(L, entity->getHitboxWidth());
    lua_settable(L, -3);

    lua_pushstring(L, "y");
    lua_pushnumber(L, entity->getHitboxHeight());
    lua_settable(L, -3);

    lua_pushvalue(L, -1);
    return 1;
}
