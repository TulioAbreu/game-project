#ifndef SCRIPTS_CORE_HPP
#define SCRIPTS_CORE_HPP

extern "C" {
    #include <lua5.1/lauxlib.h>
    #include <lua5.1/lua.h>
    #include <lua5.1/lualib.h>
};

#include <string>
#include <vector>

std::string INVALID_ARGUMENTS_ERROR(const std::string functionName, const std::string expectedType);
bool hasCorrectArgsLength(lua_State* L, const int expectedArgsLength);

#endif
