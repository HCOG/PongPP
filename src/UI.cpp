// UI.cpp
#include "UI.h"
#include <sstream>
#include <iomanip>

UI::UI(SDL_Renderer* renderer, TTF_Font* font) :
    renderer(renderer), font(font), texture(nullptr), textWidth(0), textHeight(0) {
}

UI::~UI() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void UI::UpdateVelocity(float velocity) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << "Velocity: " << velocity;
    velocityText = stream.str();
    CreateTextureFromText();
}

void UI::Render() {
    if (texture) {
        SDL_Rect renderQuad = { 10, 10, textWidth, textHeight };
        SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);
    }
}

void UI::CreateTextureFromText() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Color textColor = {255, 255, 255}; // white color
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, velocityText.c_str(), textColor);
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textWidth = textSurface->w;
    textHeight = textSurface->h;
    SDL_FreeSurface(textSurface);
}
