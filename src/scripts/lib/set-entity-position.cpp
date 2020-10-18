#include "../../entities/container/container.hpp"
#include "../core.hpp"
#include "../../utils/log/log.hpp"
#include "../library.hpp"

#define EXPECTED_ARGS_LEN 2

static auto gEntities = Entities::Container::getInstance();

int lua_setEntityPosition(lua_State* L)
{
    if (!hasCorrectArgsLength(L, EXPECTED_ARGS_LEN)) {
        return 0;
    }

    if (lua_isnumber(L, 1) == 0) {
        LOG_WARNING(INVALID_ARGUMENTS_ERROR("luaSetEntityPosition", "number"));
        return 0;
    }
    const int entityId = lua_tonumber(L, 1);

    Vector2f newPosition = {0.f, 0.f};
    if (lua_istable(L, 2) == 0) {
        LOG_WARNING(INVALID_ARGUMENTS_ERROR("luaSetEntryPosition", "table"));
        return 0;
    }

    lua_pushstring(L, "x");
    lua_gettable(L, 2);
    newPosition.x = lua_tonumber(L, -1);

    lua_pushstring(L, "y");
    lua_gettable(L, 2);
    newPosition.y = lua_tonumber(L, -1);

    auto entity = gEntities->getEntityByID(entityId);
    if (!entity) {
        return 0;
    }

    entity->setHitboxPosition(newPosition.x, newPosition.y);

    return 1;
}
