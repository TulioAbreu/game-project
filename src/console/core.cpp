#include "core.hpp"

Console::Core::Core() {
    mConsoleWindow = new Window();
    mConsolePtr = Console::getInstance();
}

void Console::Core::update() {
    if (shouldExecuteCommand()) {
        std::string commandStr (mConsolePtr->getBufferPtr());
        mConsolePtr->cleanCommandBuffer();
        mConsolePtr->log(std::string("> ") + commandStr);
        const std::string result = executeCommand(commandStr);
        if (result.size() == 0) {
            mConsolePtr->log("Success.");
        } else {
            mConsolePtr->log(result);
        }
    }
}

void Console::Core::render() {
    mConsoleWindow->render();
}

bool Console::Core::shouldExecuteCommand() const {
    return mConsoleWindow->isButtonPressed() || mConsoleWindow->isFieldTriggered();
}

std::string Console::Core::executeCommand(const std::string commandStr) {
    if (commandStr.size() == 0) return "";
    const int result = luaL_dostring(Script::mLuaState, commandStr.c_str());
    return (result == 0)
        ? ""
        : std::string(lua_tostring(Script::mLuaState, -1));
}
