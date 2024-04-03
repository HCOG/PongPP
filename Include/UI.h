#pragma once
#ifndef UI_H
#define UI_H

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

class UI {
public:
    UI(SDL_Renderer* renderer, TTF_Font* font);
    ~UI();

    void UpdateVelocity(float velocity);
    void Render();

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::string velocityText;
    SDL_Texture* texture;
    int textWidth;
    int textHeight;

    void CreateTextureFromText();
};

#endif // VELOCITY_DISPLAY_H
