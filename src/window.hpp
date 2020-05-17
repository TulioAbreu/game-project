#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "rectangle.hpp"
#include "log.hpp"
#include <iostream>
#include "vector2.hpp"
#include "sprite-manager.hpp"


class Window {
    bool mIsOpen;

    public:
    sf::RenderWindow mWindow;
    sf::Event mEvent;

    sf::RectangleShape mRectangle;

    public:
    Window(int width, int height, std::string title):
        mWindow (sf::VideoMode(width, height), title)
    {
        mWindow.setFramerateLimit(60);
        if (!mWindow.isOpen()) {
            LOG_ERROR("SFML/Window: Failed to open a window");
            mIsOpen = false;
        }
        else {
            LOG("SFML/Window: Success");
            mIsOpen = true;
        }
    }

    virtual ~Window();
    void handleWindowEvents(Vector2f& contextSize, Vector2f& halfContextSize);
    void clear();
    void display(); 
    bool isOpen(); 
    void drawRectangle(const Rectangle rect);
    void drawSprite(int spriteId, const Rectangle relativeRectangle);
    void close();
};


#endif