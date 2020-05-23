#include "window.hpp"

static SpriteManager& gSpriteManager = *SpriteManager::getInstance();

Window::~Window() {
    mWindow.close();
}

void Window::handleWindowEvents(Vector2f& contextSize, Vector2f& halfContextSize) {
    while (mWindow.pollEvent(mEvent)) {
        if (mEvent.type == sf::Event::Closed) {
            close();
        }
        if (mEvent.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, mEvent.size.width, mEvent.size.height);
            contextSize = {(float)mEvent.size.width, (float)mEvent.size.height};
            halfContextSize = contextSize*0.5f;
            mWindow.setView(sf::View(visibleArea));
        }
    }
}

void Window::clear() {
    mWindow.clear();
}

void Window::display() { 
    mWindow.display();
}

bool Window::isOpen() { 
    return mWindow.isOpen();
}

void Window::drawRectangle(const Rectangle rect) {
    mRectangle.setSize(sf::Vector2f(rect.width, rect.height));
    mRectangle.setPosition(rect.positionX, rect.positionY);
    mRectangle.setFillColor(sf::Color::Red);

    mWindow.draw(mRectangle);
}

void Window::drawSprite(int spriteId, const Rectangle relativeRectangle) {
    sf::Sprite spr (gSpriteManager.getSpriteById(spriteId));
    spr.setPosition(relativeRectangle.positionX, relativeRectangle.positionY);
    mWindow.draw(spr);
}

void Window::close() {
    mWindow.close();
    mIsOpen = false;
}
