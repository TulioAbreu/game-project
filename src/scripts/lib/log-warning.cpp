#include "../../utils/log/log.hpp"
#include "../core.hpp"
#include "../library.hpp"

int lua_logWarning(lua_State* L) {
    if (lua_gettop(L) >= 0) {
        LOG_WARNING(std::string(lua_tostring(L, -1)));
    }
    return 1;
}
