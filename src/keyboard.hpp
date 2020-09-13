#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <SFML/Window/Keyboard.hpp>
#include <map>
#include <string>
#include "utils/log/log.hpp"
#include "singleton.hpp"

class Keyboard: public Singleton<Keyboard> {
private:
    std::map<std::string, sf::Keyboard::Key> mKeyboardMap;

public:
    Keyboard() {
        instantiateKey("UP", sf::Keyboard::Up);
        instantiateKey("DOWN", sf::Keyboard::Down);
        instantiateKey("LEFT", sf::Keyboard::Left);
        instantiateKey("RIGHT", sf::Keyboard::Right);
        instantiateKey("A", sf::Keyboard::A);
        instantiateKey("E", sf::Keyboard::E);
        instantiateKey("S", sf::Keyboard::S);
        instantiateKey("W", sf::Keyboard::W);
    }

    void instantiateKey(std::string keyName, sf::Keyboard::Key scanCode) {
        mKeyboardMap[keyName] = scanCode;
    }

    bool isKeyPressed(std::string keyName) {
        return sf::Keyboard::isKeyPressed(mKeyboardMap.at(keyName));
    }
};

#endif
