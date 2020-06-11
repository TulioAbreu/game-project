#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <string>

#include "singleton.hpp"
#include "../third-party/imgui.h"
#include "../third-party/imgui-SFML.h"

const char* CONSOLE_WINDOW_TITLE = "Console";
const char* CONSOLE_BUTTON_TEXT = "Execute";

class Console: public Singleton<Console> {
private:
    std::string mCommandLog;
    char mCommandBuffer[255];

    void logMessage(std::string message) {
        mCommandLog += message + "\n";
    }

    std::string runCommand(std::string commandStr) {
        // TODO: Run command
        std::string output ("hello! :)");
        return output;
    }

    void cleanCommandBuffer() {
        mCommandBuffer[0] = '\0';
    }

public:
    Console() {
        mCommandLog = "";
        strcpy(mCommandBuffer, mCommandLog.c_str());
    }

    void onCommand() {
        std::string commandStr (mCommandBuffer);
        if (commandStr.length() == 0) return;

        cleanCommandBuffer();

        logMessage(commandStr);
        std::string output = runCommand(commandStr);
        logMessage(">" + output);
    }

    void render() {
        ImGui::Begin(CONSOLE_WINDOW_TITLE);
        if (ImGui::Button(CONSOLE_BUTTON_TEXT)) {
            onCommand();
        }
        ImGui::SameLine();
        if (ImGui::InputText("", mCommandBuffer, 255, ImGuiInputTextFlags_EnterReturnsTrue, nullptr, nullptr)) {
            onCommand();
        }
        ImGui::Separator();
        ImGui::BeginChild("scrolling");
        ImGui::Text(mCommandLog.c_str());
        ImGui::EndChild();
        ImGui::End();
    }
};

#endif
