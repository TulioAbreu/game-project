#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <string>
#include "rectangle.hpp"

#include <iostream>

class Window {
    bool mIsOpen;

    public:
    SDL_Window* mWindow;
    SDL_Renderer* mWinRenderer;

    public:
    Window(int width, int height, std::string title) {
        SDL_Init(SDL_INIT_VIDEO);
        mWindow = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_OPENGL
        );

        if (mWindow == NULL) {
            std::cerr << "Failed to open a window." << std::endl;
            mIsOpen = false;
        }
        else {
            mIsOpen = true;
            mWinRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        }
    }
    virtual ~Window() {
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
    }

    void handleWindowEvents() {
    }

    void clear() {
        SDL_SetRenderDrawColor(mWinRenderer, 0, 0, 0, 255);
        SDL_RenderClear(mWinRenderer);
    }

    void display() { SDL_RenderPresent(mWinRenderer); }

    bool isOpen() { return mIsOpen; }

    void drawRectangle(const Rectangle rect) {
        // TODO: Float/Integer conversion is causing some Input Delay
        SDL_Rect sdlRect = {
           (int)rect.positionX,
           (int)rect.positionY,
           (int)rect.width,
           (int)rect.height 
        };

        SDL_SetRenderDrawColor(mWinRenderer, 255, 0, 0, 100);
        SDL_RenderFillRect(mWinRenderer, &sdlRect);
    }
    
    void close() {
        mIsOpen = false;
    }
};


#endif