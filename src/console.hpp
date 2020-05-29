#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "../third-party/imgui.h"
#include "../third-party/imgui-SFML.h"

class Console {
private:
    std::string mLog;
    char mBuffer[255];
public:
    Console() {
        mLog = "hi\nhi\nhi\nhi\nhi\nhi\nhi\nhi\nhi\nhi\nhi\nhi\nhi\nhi\nhi\nhi\nhi\nhi\nhi\n";
        strcpy(mBuffer, mLog.c_str());
    }

    void render() {
        ImGui::Begin("Console");
        ImGui::Button("Clear");
        ImGui::SameLine();
        ImGui::InputText("Command", mBuffer, 255);
        ImGui::Separator();
        ImGui::BeginChild("scrolling");
        ImGui::Text(mBuffer);
        ImGui::EndChild();
        ImGui::End();
    }
};

#endif
