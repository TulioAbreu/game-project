#include "window.hpp"

Console::Window::Window() {
    mConsolePtr = Console::Console::getInstance();
    mButtonTriggered = false;
    mFieldTriggered = false;
}

bool Console::Window::isButtonPressed() const {
    return mButtonTriggered;
}

bool Console::Window::isFieldTriggered() const {
    return mFieldTriggered;
}

void Console::Window::render() {
    ImGui::Begin(CONSOLE_WINDOW_TITLE);
    mButtonTriggered = ImGui::Button(CONSOLE_BUTTON_TEXT);
    ImGui::SameLine();
    mFieldTriggered = ImGui::InputText("", mConsolePtr->getBufferPtr(), mConsolePtr->getBufferSize(), ImGuiInputTextFlags_EnterReturnsTrue, nullptr, nullptr);
    ImGui::Separator();
    ImGui::BeginChild("scrolling");
    ImGui::Text("%s", mConsolePtr->getLogBuffer().c_str());
    ImGui::EndChild();
    ImGui::End();
}
