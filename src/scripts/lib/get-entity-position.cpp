#include "../../entities/container/container.hpp"
#include "../core.hpp"
#include "../library.hpp"

#define EXPECTED_ARGS_LEN 1

static Entities::Container* gEntities = Entities::Container::getInstance();

int lua_getEntityPosition(lua_State* L)
{
    const size_t argsLen = lua_gettop(L);
    const size_t REQUIRED_ARGS_LEN = 1;
    if (argsLen != REQUIRED_ARGS_LEN) {
        return 0;
    }

    const int entityID = lua_tonumber(L, -1);

    Entity* entity = gEntities->getEntityByID(entityID);
    if (!entity) {
        return 0;
    }

    const Vector2f entityPosition(entity->getHitboxPositionX(),
                                  entity->getHitboxPositionY());

    lua_newtable(L);

    lua_pushstring(L, "x");
    lua_pushnumber(L, entity->getHitboxPositionX());
    lua_settable(L, -3);

    lua_pushstring(L, "y");
    lua_pushnumber(L, entity->getHitboxPositionY());
    lua_settable(L, -3);

    lua_pushvalue(L, -1);
    return 1;
}
