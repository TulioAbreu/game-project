#ifndef SCRIPT_MANAGER
#define SCRIPT_MANAGER
#include <cstdio>
#include <string>
extern "C" {
    #include <lua5.1/lauxlib.h>
    #include <lua5.1/lua.h>
    #include <lua5.1/lualib.h>
};


class Script {
    private:
    static bool mIsLibLoaded;
    std::string mFilePath;
    std::string mName;
    bool mIsReady;
    bool loadFile();
    bool runFile();
    static void loadLuaLibraries(lua_State* luaState);
    static void registerFunction(lua_State* luaState, std::string functionName, lua_CFunction f);

    public:
    static lua_State* mLuaState;
    Script(std::string filePath, std::string name);
    std::string getName();
    void loadFunction(std::string functionName);
    void lua_executeFunction(int argsLen);
    void runScriptFromString(std::string codeStr);
    void onStart(int entityID);
    void onUpdate(int entityID);
    void onDestroy(int entityID);
};


#endif