#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "rectangle.hpp"

class Window {
    sf::Event mEvent;
    sf::RectangleShape mRect;

    public:
    sf::RenderWindow mWindow;

    public:
    Window(int width, int height, std::string title) : mWindow(sf::VideoMode(width, height), title) {
        mWindow.setFramerateLimit(60);
    }
    virtual ~Window() = default;

    void handleWindowEvents() {
        while (mWindow.pollEvent(mEvent)) {
            if (mEvent.type == sf::Event::Closed) {
                // TODO: Maybe add some kind of callback to window class?
                mWindow.close();
            }
        }
    }

    void clear() { mWindow.clear(); }

    void display() { mWindow.display(); }

    bool isOpen() { return mWindow.isOpen(); }

    void drawRectangle(const Rectangle rect) {
        sf::RectangleShape dRect;
        dRect.setPosition(rect.position.x, rect.position.y);
        dRect.setSize(sf::Vector2f(rect.width, rect.height));

        dRect.setOutlineColor(sf::Color::Red);
        dRect.setOutlineThickness(1);
        dRect.setFillColor(sf::Color(0, 0, 0, 0));

        mWindow.draw(dRect);
    }
};


#endif