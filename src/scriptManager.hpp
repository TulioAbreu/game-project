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

#define LUA_REGISTERFUNCTION(state, functionName, function) \
    lua_pushcfunction(state, function);                     \
    lua_setglobal(state, functionName);


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

            LUA_REGISTERFUNCTION(mLuaState, "log", lua_log);
            LUA_REGISTERFUNCTION(mLuaState, "logWarning", lua_logWarning);
            LUA_REGISTERFUNCTION(mLuaState, "logError", lua_logError);

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
    }

    void onUpdate(int entityId) {
        loadFunction(mName + "_OnUpdate");
        lua_pushnumber(mLuaState, entityId);
        runFunction(1);
    }

    void onDestroy(int entityID) {
        loadFunction(mName + "_OnDestroy");
        lua_pushnumber(mLuaState, entityID);
        runFunction(1);
    }
};

lua_State* Script::mLuaState = luaL_newstate();
bool Script::mIsLibLoaded = false;

#endif