#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <SDL.h>
#include <map>
#include <string>
#include "log.hpp"

class Keyboard {
private:
    std::map<std::string, SDL_Scancode> mKeyboardMap;

public:
    Keyboard() {
        instantiateKey("UP", SDL_SCANCODE_UP);
        instantiateKey("DOWN", SDL_SCANCODE_DOWN);
        instantiateKey("LEFT", SDL_SCANCODE_LEFT);
        instantiateKey("RIGHT", SDL_SCANCODE_RIGHT);
        instantiateKey("A", SDL_SCANCODE_A);
        instantiateKey("E", SDL_SCANCODE_E);
        instantiateKey("S", SDL_SCANCODE_S);
        instantiateKey("W", SDL_SCANCODE_W);
    }

    void instantiateKey(std::string keyName, SDL_Scancode scanCode) {
        mKeyboardMap[keyName] = scanCode;
    }

    bool isKeyPressed(std::string keyName) {
        const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
        if (!keyboardState) {
            std::cout << ERROR_PREFIX << "Keyboard/SDL Error: Could not get keyboard state." << std::endl;
            return false;
        }
        // if (!mKeyboardMap.contains(keyName)) {
        //     std::cout << WARNING_PREFIX << "Keyboard: Specified keyName was not found. (keyName='" << keyName << "')" << std::endl;
        //     return false;
        // }

        return keyboardState[mKeyboardMap.at(keyName)];
    }
};

#endif
