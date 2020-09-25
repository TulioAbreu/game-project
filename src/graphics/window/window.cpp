#include "window.hpp"
#include "../../../third-party/imgui.h"
#include "../../../third-party/imgui-SFML.h"

static Sprites::Manager& gSpriteManager = *Sprites::Manager::getInstance();

Graphics::Window::Window(int width, int height, std::string title):
    mWindow (sf::VideoMode(width, height), title) 
{
    mWindow.setFramerateLimit(60);
    mUnfocusLimitFrames = true;
    if (!mWindow.isOpen()) {
        LOG_ERROR("SFML/Window: Failed to open a window");
    } else {
        LOG("SFML/Window: Success");
    }
    startImgui();
}

Graphics::Window::~Window() {
    mWindow.close();
    ImGui::SFML::Shutdown();
}

void Graphics::Window::startImgui() {
    ImGui::SFML::Init(mWindow);
}

void Graphics::Window::handleWindowEvents(Vector2f& contextSize) {
    if (!isOpen()) {
        return;
    }

    Vector2f halfContextSize = contextSize*.5f;

    while (mWindow.pollEvent(mEvent)) {
        ImGui::SFML::ProcessEvent(mEvent);
        switch (mEvent.type) {
            case sf::Event::Closed: {
                close();
            } break;
            case sf::Event::Resized: {
                sf::FloatRect visibleArea(0, 0, mEvent.size.width, mEvent.size.height);
                contextSize = {(float)mEvent.size.width, (float)mEvent.size.height};
                halfContextSize = contextSize*0.5f;
                mWindow.setView(sf::View(visibleArea));
            } break;
            case sf::Event::GainedFocus: {
                if (mUnfocusLimitFrames) {
                    mWindow.setFramerateLimit(DEFAULT_FOCUS_FRAMERATE);
                    LOG("Window/HandleWindowEvents: Gained window focus. FrameRate set to " << DEFAULT_FOCUS_FRAMERATE);
                }
            } break;
            case sf::Event::LostFocus: {
                if (mUnfocusLimitFrames) {
                    mWindow.setFramerateLimit(DEFAULT_UNFOCUS_FRAMERATE);
                    LOG("Window/HandleWindowEvents: Lost window focus. FrameRate set to " << DEFAULT_UNFOCUS_FRAMERATE);
                }
            }
            default: {
                // Do nothing.
            }
        }
    }

    ImGui::SFML::Update(mWindow, sf::milliseconds(16));
}

void Graphics::Window::clear() {
    if (!isOpen()) {
        return;
    }

    mWindow.clear();
}

void Graphics::Window::display() {
    if (!isOpen()) {
        return;
    }

    ImGui::SFML::Render(mWindow);
    mWindow.display();
}

bool Graphics::Window::isOpen() { 
    return mWindow.isOpen();
}

void Graphics::Window::drawRectangle(const Rectangle rect) {
    if (!isOpen()) {
        return;
    }

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(rect.width, rect.height));
    rectangle.setPosition(rect.positionX, rect.positionY);
    rectangle.setFillColor(sf::Color::Red);

    mWindow.draw(rectangle);
}

void Graphics::Window::drawSprite(int spriteId, const Rectangle relativeRectangle) {
    if (!isOpen()) {
        return;
    }

    sf::Sprite spr (gSpriteManager.getSpriteById(spriteId));
    spr.setPosition(relativeRectangle.positionX, relativeRectangle.positionY);
    mWindow.draw(spr);
}

void Graphics::Window::close() {
    ImGui::SFML::Shutdown();
    mWindow.close();
}

Vector2f Graphics::Window::getWindowSize() const {
    sf::Vector2u sfmlSize = mWindow.getSize();
    return {
        (float) sfmlSize.x,
        (float) sfmlSize.y
    };
}
