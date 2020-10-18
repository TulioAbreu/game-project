#ifndef SCRIPTS_LIB_LIBRARY_HPP
#define SCRIPTS_LIB_LIBRARY_HPP

#include "../singleton.hpp"
#include "core.hpp"
#include <string>

// Log
int lua_log(lua_State* L);
int lua_logWarning(lua_State* L);
int lua_logError(lua_State* L);
// Entity Size
int lua_getEntitySize(lua_State* L);
int lua_setEntitySize(lua_State* L);
// Entity Width
int lua_setEntityWidth(lua_State* L);
int lua_getEntityWidth(lua_State* L);
// Entity Position
int lua_getEntityPosition(lua_State* L);
int lua_setEntityPosition(lua_State* L);
// Keyboard
int lua_getIsKeyPressed(lua_State* L);

#endif
