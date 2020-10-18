#include "core.hpp"

std::string INVALID_ARGUMENTS_ERROR(const std::string functionName, const std::string expectedType)
{
    return functionName + ": Invalid argument. Expected " + expectedType;
}

bool hasCorrectArgsLength(lua_State* L, const int expectedArgsLength)
{
    const size_t callArgsLength = lua_gettop(L);
    return callArgsLength == expectedArgsLength;
}
