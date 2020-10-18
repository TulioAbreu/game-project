#include "../../keyboard.hpp"
#include "../core.hpp"
#include "../../utils/log/log.hpp"
#include "../library.hpp"

#define EXPECTED_ARGS_LEN 1

static Keyboard* gKeyboard = Keyboard::getInstance();

int lua_getIsKeyPressed(lua_State* L)
{
    if (!hasCorrectArgsLength(L, EXPECTED_ARGS_LEN)) {
        return 0;
    }

    if (lua_isstring(L, 1) == 0) {
        LOG_WARNING(INVALID_ARGUMENTS_ERROR("luaGetIsKeyPressed", "string"));
        return 0;
    }

    const std::string keyName = lua_tostring(L, 1);
    const bool isKeyPressed = gKeyboard->isKeyPressed(keyName);
    lua_pushboolean(L, isKeyPressed);

    return 1;
}
