#ifndef SCRIPT_MANAGER
#define SCRIPT_MANAGER
#include <cstdio>
#include <string>
extern "C" {
    #include <lua5.1/lauxlib.h>
    #include <lua5.1/lua.h>
    #include <lua5.1/lualib.h>
};

#include "log.hpp"


int lua_setEntityPositionX(lua_State* mLuaState) {
    LOG("Entity X Position was set to 0");
    return 1;
}


// TODO: Singleton
class Script {
private:
    static lua_State* mLuaState;
    static bool mIsLibLoaded;

    std::string mFilePath;
    std::string mName;
    bool mIsReady;

    bool loadFile() {
        if (luaL_loadfile(mLuaState, mFilePath.c_str())) {
            LOG_WARNING("Failed to load script \"" << mFilePath  << "\"");
            return false;
        }
        return true;
    }

    bool runFile() {
        if (lua_pcall(mLuaState, 0, LUA_MULTRET, 0)) {
            LOG_WARNING("Failed to run script \"" << mFilePath  << "\"");
            return false;
        }
        return true;
    }
public:
    Script(std::string filePath, std::string name) {
        if (!mIsLibLoaded) {
            luaL_openlibs(mLuaState);
            mIsLibLoaded = true;
        }

        mFilePath = filePath;
        mName = name;

        if (! this->loadFile()) {
            mIsReady = false;
            return;
        }
        if (! this->runFile()) {
            mIsReady = false;
            return;
        }

        mIsReady = true;
    }

    // lua_getglobal(L, "start");
    // lua_pushnumber(L, 5);
    // lua_pcall(L, 1, 1, 0);
    // cout << "The return value of the function was " << lua_tostring(L, -1) << endl;
    // lua_pop(L,1);

    void loadFunction(std::string functionName) {
        lua_getglobal(mLuaState, functionName.c_str());
    }

    void runFunction(int argsLen) {
        lua_pcall(mLuaState, argsLen, 1, 0);
        lua_pop(mLuaState, 1);
    }

    void onStart(int entityId) {
        loadFunction(mName + "_OnStart");
        lua_pushnumber(mLuaState, entityId);
        runFunction(1);

        // loadFunction("monster_OnStart");
        // lua_pushnumber(mLuaState, entityId);
        // runFunction(1);

        // lua_getglobal(mLuaState, "monster_onStart");
        // lua_pcall(mLuaState, 1, 1, 0);
        // lua_pop(mLuaState, 1);
    }

    void onUpdate(int entityId) {
        loadFunction(mName + "_OnUpdate");
        lua_pushnumber(mLuaState, entityId);
        runFunction(1);
    }
};

lua_State* Script::mLuaState = luaL_newstate();
bool Script::mIsLibLoaded = false;

// void exposeFunction() {
//     lua_pushcfunction(mLuaState, resetPlayerPosition);
//     lua_setglobal(mLuaState, "resetPlayerPosition");
// }

#endif