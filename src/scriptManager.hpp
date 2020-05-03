#ifndef SCRIPT_MANAGER
#define SCRIPT_MANAGER
#include <cstdio>
#include <string>
extern "C" {
    #include <lua5.1/lauxlib.h>
    #include <lua5.1/lua.h>
    #include <lua5.1/lualib.h>
};

int lua_log(lua_State* mLuaState);
int lua_logWarning(lua_State* mLuaState);
int lua_logError(lua_State* mLuaState);

// Entity Width
int lua_setEntityWidth(lua_State* mLuaState);
int lua_getEntityWidth(lua_State* mLuaState);
// Entity Position X
int lua_getEntityPositionX(lua_State* mLuaState);
int lua_setEntityPositionX(lua_State* mLuaState);
// Entity Position Y
int lua_getEntityPositionY(lua_State* mLuaState);
int lua_setEntityPositionY(lua_State* mLuaState);

class Script {
private:
    static lua_State* mLuaState;
    static bool mIsLibLoaded;

    std::string mFilePath;
    std::string mName;
    bool mIsReady;

    bool loadFile();

    bool runFile();

    static void loadLuaLibraries(lua_State* luaState);

    static void registerFunction(lua_State* luaState, std::string functionName, lua_CFunction f);
public:
    Script(std::string filePath, std::string name);

    void loadFunction(std::string functionName);

    void lua_executeFunction(int argsLen);

    void onStart(int entityID);

    void onUpdate(int entityID);

    void onDestroy(int entityID);
};


#endif