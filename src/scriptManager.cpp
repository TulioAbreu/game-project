#include "scriptManager.hpp"
#include "entity-container.hpp"
#include "log.hpp"
#include "script-library.hpp"


lua_State* Script::mLuaState = luaL_newstate();
bool Script::mIsLibLoaded = false;

void Script::loadLuaLibraries(lua_State* luaState) {
    luaL_openlibs(mLuaState);
    registerFunction(mLuaState, "log", lua_log);
    registerFunction(mLuaState, "logWarning", lua_logWarning);
    registerFunction(mLuaState, "logError", lua_logError);
    // Width
    registerFunction(mLuaState, "setEntityWidth", lua_setEntityWidth);
    registerFunction(mLuaState, "getEntityWidth", lua_getEntityWidth);
    // Position X
    registerFunction(mLuaState, "setEntityPositionX", lua_setEntityPositionX);
    registerFunction(mLuaState, "getEntityPositionX", lua_getEntityPositionX);
    // Position Y
    registerFunction(mLuaState, "setEntityPositionY", lua_setEntityPositionY);
    registerFunction(mLuaState, "getEntityPositionY", lua_getEntityPositionY);
}

void Script::registerFunction(lua_State* luaState, std::string functionName, lua_CFunction f) {
    lua_pushcfunction(luaState, f);
    lua_setglobal(luaState, functionName.c_str());
}

bool Script::loadFile() {
    if (luaL_loadfile(mLuaState, mFilePath.c_str())) {
        LOG_WARNING("Failed to load script \"" << mFilePath  << "\"");
        return false;
    }
    return true;
}

bool Script::runFile() {
    if (lua_pcall(mLuaState, 0, LUA_MULTRET, 0)) {
        LOG_WARNING("Failed to run script \"" << mFilePath  << "\"");
        return false;
    }
    return true;
}

Script::Script(std::string filePath, std::string name) {
    if (!mIsLibLoaded) {
        loadLuaLibraries(mLuaState);
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

void Script::loadFunction(std::string functionName) {
    lua_getglobal(mLuaState, functionName.c_str());
}

void Script::lua_executeFunction(int argsLen) {
    lua_pcall(mLuaState, argsLen, 1, 0);
    lua_pop(mLuaState, 1);
}

void Script::onStart(int entityID) {
    loadFunction(mName + "_OnStart");
    lua_pushnumber(mLuaState, entityID);
    lua_executeFunction(1);
}

void Script::onUpdate(int entityID) {
    loadFunction(mName + "_OnUpdate");
    lua_pushnumber(mLuaState, entityID);
    lua_executeFunction(1);
}

void Script::onDestroy(int entityID) {
    loadFunction(mName + "_OnDestroy");
    lua_pushnumber(mLuaState, entityID);
    lua_executeFunction(1);
}
