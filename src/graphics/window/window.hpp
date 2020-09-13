#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "../../rectangle.hpp"
#include "../../utils/log/log.hpp"
#include "../../utils/vector2/vector2.hpp"
#include "../../sprite-manager.hpp"

namespace Graphics { 
class Window {
    private:
    void startImgui();

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
        }
        else {
            LOG("SFML/Window: Success");
        }
        startImgui();
    }

    virtual ~Window();
    void handleWindowEvents(Vector2f& contextSize);
    void clear();
    void display(); 
    bool isOpen(); 
    void drawRectangle(const Rectangle rect);
    void drawSprite(int spriteId, const Rectangle relativeRectangle);
    void close();
};};

#endif