#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "rectangle.hpp"
#include "log.hpp"
#include <iostream>

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
        if (!mWindow.isOpen()) {
            LOG_ERROR("SFML/Window: Failed to open a window");
            mIsOpen = false;
        }
        else {
            LOG("SFML/Window: Success");
            mIsOpen = true;
        }
    }

    virtual ~Window() {
        mWindow.close();
    }

    void handleWindowEvents() {
        while (mWindow.pollEvent(mEvent)) {
            if (mEvent.type == sf::Event::Closed) {
                close();
            }
        }
    }

    void clear() {
        mWindow.clear();
    }

    void display() { 
        mWindow.display();
    }

    bool isOpen() { 
        return mWindow.isOpen();
    }

    void drawRectangle(const Rectangle rect) {
        mRectangle.setSize(sf::Vector2f(rect.width, rect.height));
        mRectangle.setPosition(rect.positionX, rect.positionY);
        mRectangle.setFillColor(sf::Color::Red);

        mWindow.draw(mRectangle);
    }
    
    void close() {
        mIsOpen = false;
    }
};


#endif