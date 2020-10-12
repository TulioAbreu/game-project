#ifndef CONSOLE_CONSOLE_HPP
#define CONSOLE_CONSOLE_HPP

#include "../singleton.hpp"
#include <string>
#include <vector>

#define CONSOLE_MAX_LOG_SIZE 30
#define CONSOLE_BUFFER_SIZE 255

namespace Console {
class Console : public Singleton<Console> {
public:
    void cleanCommandBuffer();
    void clean();
    void log(std::string message);
    const std::string getLogBuffer() const;
    char* getBufferPtr();
    int getBufferSize() const;
private:
    std::vector<std::string> mCommandLog;
    std::string mCommandLogBuffer;
    char mCommandBuffer[CONSOLE_BUFFER_SIZE];
    void updateLog();
};
};

#endif
