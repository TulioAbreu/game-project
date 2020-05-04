#include "script-library.hpp"
#include "log.hpp"

static Entities* gEntities = Entities::getInstance();

int lua_setEntityWidth(lua_State* mLuaState) {
    const size_t argsLen = lua_gettop(mLuaState);
    const size_t REQUIRED_ARGS_LEN = 2;
    if (argsLen != REQUIRED_ARGS_LEN) {
        return 0;
    }

    const int entityID = lua_tonumber(mLuaState, 1);
    const int width = lua_tonumber(mLuaState, 2);

    Entity* entity = gEntities->getEntityByID(entityID);
    entity->setHitboxWidth(width);

    return 1;
}

int lua_getEntityPositionX(lua_State* mLuaState) {
    const size_t argsLen = lua_gettop(mLuaState);
    const size_t REQUIRED_ARGS_LEN = 1;
    if (argsLen != REQUIRED_ARGS_LEN) {
        return 0;
    }

    const int entityID = lua_tonumber(mLuaState, 1);

    Entity* entity = gEntities->getEntityByID(entityID);
    if (!entity) {
        return 0;
    }

    const int entityPositionX = entity->getHitboxPositionX();
    lua_pushnumber(mLuaState, entityPositionX);

    return 1;
}

int lua_setEntityPositionX(lua_State* mLuaState) {
    const size_t argsLen = lua_gettop(mLuaState);
    const size_t REQUIRED_ARGS_LEN = 2;
    if (argsLen != REQUIRED_ARGS_LEN) {
        return 0;
    }

    const int entityID = lua_tonumber(mLuaState, 1);
    const int positionX = lua_tonumber(mLuaState, 2);
 
    Entity* entity = gEntities->getEntityByID(entityID);
    if (!entity) {
        return 0;
    }

    entity->setHitboxPositionX(positionX);

    return 0;
}

int lua_getEntityPositionY(lua_State* mLuaState) {
    const size_t argsLen = lua_gettop(mLuaState);
    const size_t REQUIRED_ARGS_LEN = 1;
    if (argsLen != REQUIRED_ARGS_LEN) {
        return 0;
    }

    const int entityID = lua_tonumber(mLuaState, 1);

    Entity* entity = gEntities->getEntityByID(entityID);
    if (!entity) {
        return 0;
    }

    const int entityPositionY = entity->getHitboxPositionY();
    lua_pushnumber(mLuaState, entityPositionY);

    return 1;
}

int lua_setEntityPositionY(lua_State* mLuaState) {
    const size_t argsLen = lua_gettop(mLuaState);
    const size_t REQUIRED_ARGS_LEN = 2;
    if (argsLen != REQUIRED_ARGS_LEN) {
        return 0;
    }

    const int entityID = lua_tonumber(mLuaState, 1);
    const int positionY= lua_tonumber(mLuaState, 2);
 
    Entity* entity = gEntities->getEntityByID(entityID);
    if (!entity) {
        return 0;
    }

    entity->setHitboxPositionY(positionY);

    return 0;
}


int lua_log(lua_State* mLuaState) {
    if (lua_gettop(mLuaState) >= 0) {
        LOG(std::string(lua_tostring(mLuaState, -1)));
    }
    return 1;
}

int lua_logWarning(lua_State* mLuaState) {
    if (lua_gettop(mLuaState) >= 0) {
        LOG_WARNING(std::string(lua_tostring(mLuaState, -1)));
    }
    return 1;
}

int lua_logError(lua_State* mLuaState) {
    if (lua_gettop(mLuaState) >= 0) {
        LOG_ERROR(std::string(lua_tostring(mLuaState, -1)));
    }
    return 1;
}

int lua_getEntityWidth(lua_State* mLuaState) {
    const size_t argsLen = lua_gettop(mLuaState);
    const size_t REQUIRED_ARGS_LEN = 1;
    if (argsLen != REQUIRED_ARGS_LEN) {
        return 0;
    }

    const int entityID = lua_tonumber(mLuaState, 1);

    Entity* entity = gEntities->getEntityByID(entityID);
    if (!entity) {
        return 0;
    }

    const int entityPositionX = entity->getHitboxPositionX();
    lua_pushnumber(mLuaState, entityPositionX);

    return 1;
}

