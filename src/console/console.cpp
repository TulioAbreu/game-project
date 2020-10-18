#include "console.hpp"

void Console::Console::updateLog() {
    if (mCommandLog.size() >= CONSOLE_MAX_LOG_SIZE) {
        mCommandLog.erase(mCommandLog.begin());
    }
}

void Console::Console::cleanCommandBuffer() {
    mCommandBuffer[0] = '\0';
}

void Console::Console::clean() {
    mCommandLog.clear();
    mCommandLogBuffer = "";
}

void Console::Console::log(std::string message) {
    mCommandLog.push_back(message);
    mCommandLogBuffer += message + "\n";
    updateLog();
}

const std::string Console::Console::getLogBuffer() const {
    return mCommandLogBuffer;
}

char* Console::Console::getBufferPtr() {
    return mCommandBuffer;
}

int Console::Console::getBufferSize() const {
    return CONSOLE_BUFFER_SIZE;
}
