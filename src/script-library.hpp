#ifndef SCRIPT_LIBRARY
#define SCRIPT_LIBRARY

#include "script-manager.hpp"
#include "entities/container/container.hpp"

/*
    IMPORTANT:
    On exposing new scripts, dont forget to register the new function
    at scriptManager.hpp
*/

// Logging
int lua_log(lua_State* mLuaState);
int lua_logWarning(lua_State* mLuaState);
int lua_logError(lua_State* mLuaState);
// Entity Width
int lua_setEntityWidth(lua_State* mLuaState);
int lua_getEntityWidth(lua_State* mLuaState);
// Entity Position X
int lua_getEntityPositionX(lua_State* mLuaState);
int lua_setEntityPositionX(lua_State* mLuaState);
// Entity Position Y
int lua_getEntityPositionY(lua_State* mLuaState);
int lua_setEntityPositionY(lua_State* mLuaState);
// Keyboard
int lua_getIsKeyPressed(lua_State* mLuaState);

#endif