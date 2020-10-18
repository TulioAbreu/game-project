#include <string>
#include "script-library.hpp"
#include "utils/log/log.hpp"
#include "keyboard.hpp"

static Keyboard* gKeyboard = Keyboard::getInstance();
static Entities::Container* gEntities = Entities::Container::getInstance();


int lua_setEntityWidth(lua_State* L) {
    const size_t argsLen = lua_gettop(L);
    const size_t REQUIRED_ARGS_LEN = 2;
    if (argsLen != REQUIRED_ARGS_LEN) {
        return 0;
    }

    const int entityID = lua_tonumber(L, 1);
    const int width = lua_tonumber(L, 2);

    Entity* entity = gEntities->getEntityByID(entityID);
    entity->setHitboxWidth(width);

    return 1;
}

int lua_log(lua_State* L) {
    if (lua_gettop(L) >= 0) {
        LOG(std::string(lua_tostring(L, -1)));
    }
    return 1;
}

int lua_logWarning(lua_State* L) {
    if (lua_gettop(L) >= 0) {
        LOG_WARNING(std::string(lua_tostring(L, -1)));
    }
    return 1;
}

int lua_logError(lua_State* L) {
    if (lua_gettop(L) >= 0) {
        LOG_ERROR(std::string(lua_tostring(L, -1)));
    }
    return 1;
}

int lua_getEntityWidth(lua_State* L) {
    const size_t argsLen = lua_gettop(L);
    const size_t REQUIRED_ARGS_LEN = 1;
    if (argsLen != REQUIRED_ARGS_LEN) {
        return 0;
    }

    const int entityID = lua_tonumber(L, 1);

    Entity* entity = gEntities->getEntityByID(entityID);
    if (!entity) {
        return 0;
    }

    const int entityPositionX = entity->getHitboxPositionX();
    lua_pushnumber(L, entityPositionX);

    return 1;
}

int lua_getIsKeyPressed(lua_State* L) {
    const size_t argsLen = lua_gettop(L);
    const size_t REQUIRED_ARGS_LEN = 1;
    if (argsLen != REQUIRED_ARGS_LEN) {
        return 0;
    }

    if (lua_isstring(L, 1) == 0) {
        LOG_WARNING("luaGetIsKeyPressed: Invalid argument. Expected string.");
        return 0;
    }
    const std::string keyName = lua_tostring(L, 1);
    const bool result = gKeyboard->isKeyPressed(keyName);
    lua_pushboolean(L, result);

    return 1;
}

int lua_getEntityPosition(lua_State* L) {
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

    const Vector2f entityPosition (
        entity->getHitboxPositionX(),
        entity->getHitboxPositionY()
    );

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

int lua_setEntityPosition(lua_State* L) {
    const size_t argsLen = lua_gettop(L);
    const size_t REQUIRED_ARGS_LEN = 2;
    if (argsLen != REQUIRED_ARGS_LEN) {
        return 0;
    }

    if (lua_isnumber(L, 1) == 0) {
        LOG_WARNING("luaSetEntityPosition: Invalid argument. Expected a number.");
        return 0;
    }
    const int entityId =  lua_tonumber(L, 1);

    Vector2f newPosition = {0.f, 0.f};
    if (lua_istable(L, 2) == 0) {
        LOG_WARNING("luaSetEntryPosition: Invalid argument. Expected a table.");
        return 0;
    }

    lua_pushstring(L, "x");
    lua_gettable(L, 2);
    newPosition.x = lua_tonumber(L, -1);

    lua_pushstring(L, "y");
    lua_gettable(L, 2);
    newPosition.y = lua_tonumber(L, -1);

    Entity* entity = gEntities->getEntityByID(entityId);
    if (!entity) {
        return 0;
    }

    entity->setHitboxPosition(newPosition.x, newPosition.y);

    return 1;
}

static bool lua_checkArgsLen(lua_State* L, const std::string functionName, const size_t expectedArgsLen) {
    const size_t argsLen = lua_gettop(L);
    if (argsLen != expectedArgsLen) {
        LOG_WARNING(functionName << ": Invalid arguments size. Expected " << expectedArgsLen << " arguments.");
        return false;
    }
    return true;
}

int lua_getEntitySize(lua_State* L) {
    if (!lua_checkArgsLen(L, "luaGetEntitySize", 1)) {
        return 0;
    }

    if (lua_isnumber(L, 1) == 0) {
        LOG_WARNING("luaGetEntitySize: Invalid argument type. Expected a number.");
        return 0;
    }
    const int entityId = lua_tonumber(L, 1);

    Entity* entityPtr = gEntities->getEntityByID(entityId);
    if (!entityPtr) {
        return 0;
    }

    lua_newtable(L);

    lua_pushstring(L, "x");
    lua_pushnumber(L, entityPtr->getHitboxWidth());
    lua_settable(L, -3);

    lua_pushstring(L, "y");
    lua_pushnumber(L, entityPtr->getHitboxHeight());
    lua_settable(L, -3);

    lua_pushvalue(L, -1);
    return 1;
}

int lua_setEntitySize(lua_State* L) {

    return 1;
}
