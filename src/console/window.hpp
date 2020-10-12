#ifndef CONSOLE_RENDER_HPP
#define CONSOLE_RENDER_HPP

#include "../../third-party/imgui-SFML.h"
#include "../../third-party/imgui.h"
#include "./console.hpp"

#define CONSOLE_WINDOW_TITLE "Console"
#define CONSOLE_BUTTON_TEXT "Run"

namespace Console {
class Window {
public:
    Window();
    void render();
    bool isButtonPressed() const;
    bool isFieldTriggered() const;
private:
    Console* mConsolePtr;
    bool mButtonTriggered;
    bool mFieldTriggered;
};
}

#endif
