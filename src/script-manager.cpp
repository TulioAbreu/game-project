#include "script-manager.hpp"
#include "entities/container/container.hpp"
#include "utils/log/log.hpp"

void Script::loadLuaLibraries(lua_State* luaState)
{
    luaL_openlibs(luaState);

    lua_register(luaState, "log", lua_log);
    lua_register(luaState, "logWarning", lua_logWarning);
    lua_register(luaState, "logError", lua_logError);
    // Position
    lua_register(luaState, "getEntityPosition", lua_getEntityPosition);
    lua_register(luaState, "setEntityPosition", lua_setEntityPosition);
    // Size
    lua_register(luaState, "getEntitySize", lua_getEntitySize);
    lua_register(luaState, "setEntitySize", lua_setEntitySize);
    // Keyboard
    lua_register(luaState, "getIsKeyPressed", lua_getIsKeyPressed);
}

void Script::registerFunction(lua_State* luaState, std::string functionName, lua_CFunction f)
{
    lua_register(luaState, functionName.c_str(), f);
}

bool Script::loadFile()
{
    if (luaL_loadfile(mLuaState, mFilePath.c_str())) {
        LOG_WARNING("Failed to load script \"" << mFilePath << "\"");
        return false;
    }
    return true;
}

bool Script::runFile()
{
    if (lua_pcall(mLuaState, 0, LUA_MULTRET, 0)) {
        LOG_WARNING("Failed to run script \"" << mFilePath << "\"");
        return false;
    }
    return true;
}

Script::Script(std::string filePath, std::string name)
{
    mLuaState = luaL_newstate();
    loadLuaLibraries(mLuaState);

    mFilePath = filePath;
    mName = name;

    if (!loadFile()) {
        mIsReady = false;
        return;
    }
    if (!this->runFile()) {
        mIsReady = false;
        return;
    }

    mIsReady = true;
}

void Script::loadFunction(std::string functionName)
{
    lua_getglobal(mLuaState, functionName.c_str());
}

void Script::lua_executeFunction(int argsLen)
{
    lua_pcall(mLuaState, argsLen, 1, 0);
    lua_pop(mLuaState, 1);
}

void Script::onStart(int entityID)
{
    loadFunction("OnStart");
    lua_pushnumber(mLuaState, entityID);
    lua_executeFunction(1);
}

void Script::onUpdate(int entityID)
{
    loadFunction("OnUpdate");
    lua_pushnumber(mLuaState, entityID);
    lua_executeFunction(1);
}

void Script::onDestroy(int entityID)
{
    loadFunction("OnDestroy");
    lua_pushnumber(mLuaState, entityID);
    lua_executeFunction(1);
}

std::string Script::getName()
{
    return this->mName;
}

bool Script::doString(std::string commandStr)
{
    if (commandStr.size() == 0) return false;
    const int result = luaL_dostring(mLuaState, commandStr.c_str());
    return (result != 0);
}
