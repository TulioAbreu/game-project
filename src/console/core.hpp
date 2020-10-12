#ifndef CONSOLE_CORE_HPP
#define CONSOLE_CORE_HPP

#include "../script-manager.hpp"
#include "window.hpp"
#include "console.hpp"

namespace Console {
class Core {
public:
    Core();
    void update();
    void render();
private:
    Console* mConsolePtr;
    Window* mConsoleWindow;
    std::string executeCommand(const std::string commandStr);
    bool shouldExecuteCommand() const;
};
};

#endif
