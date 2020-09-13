#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "../../rectangle.hpp"
#include "../../utils/log/log.hpp"
#include "../../utils/vector2/vector2.hpp"
#include "../../sprite-manager.hpp"

namespace Graphics { 
const int DEFAULT_FOCUS_FRAMERATE = 60;
const int DEFAULT_UNFOCUS_FRAMERATE = 5;

class Window {
    private:
    void startImgui();

    public:
    sf::RenderWindow mWindow;
    sf::Event mEvent;
    bool mUnfocusLimitFrames;

    Window(int width, int height, std::string title);
    virtual ~Window();
    void handleWindowEvents(Vector2f& contextSize);
    void clear();
    void display(); 
    bool isOpen(); 
    void drawRectangle(const Rectangle rect);
    void drawSprite(int spriteId, const Rectangle relativeRectangle);
    void close();
    Vector2f getWindowSize() const;
};};

#endif