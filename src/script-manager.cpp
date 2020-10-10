#include "script-manager.hpp"
#include "entities/container/container.hpp"
#include "utils/log/log.hpp"
#include "script-library.hpp"


lua_State* Script::mLuaState = luaL_newstate();
bool Script::mIsLibLoaded = false;

void Script::loadLuaLibraries(lua_State* luaState) {
    luaL_openlibs(mLuaState);

    lua_register(mLuaState, "log", lua_log);
    lua_register(mLuaState, "logWarning", lua_logWarning);
    lua_register(mLuaState, "logError", lua_logError);
    // Position
    lua_register(mLuaState, "getEntityPosition", lua_getEntityPosition);
    lua_register(mLuaState, "setEntityPosition", lua_setEntityPosition);
    // Size
    lua_register(mLuaState, "getEntitySize", lua_getEntitySize);
    lua_register(mLuaState, "setEntityState", lua_setEntitySize);
    // Keyboard
    lua_register(mLuaState, "getIsKeyPressed", lua_getIsKeyPressed);
}

void Script::registerFunction(lua_State* luaState, std::string functionName, lua_CFunction f) {
    lua_register(luaState, functionName.c_str(), f);
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

std::string Script::getName() {
    return this->mName;
}

void Script::runScriptFromString(std::string codeStr) {
    std::string wrapperFunction = "function buffer()\n" + codeStr + "\nend";
    lua_getglobal(mLuaState, wrapperFunction.c_str());
    loadFunction("buffer");
    lua_executeFunction(0);
}
