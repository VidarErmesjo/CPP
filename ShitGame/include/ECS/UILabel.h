#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "EntityComponentSystem.h"
#include "../AssetManager.h"
#include "../Game.h"

class UILabel: public Component
{
    SDL_Rect position;
    SDL_Color textColor;
    SDL_Texture *texture;
    std::string labelText;
    std::string labelFont;

public:
    UILabel(int x, int y, std::string text, std::string font, SDL_Color color)
    :   textColor(color), labelText(text), labelFont(font)
    {
        position.x = x;
        position.y = y;

        setLabelText(labelText, labelFont);
    }

    ~UILabel()
    {}

    void setLabelText(std::string text, std::string font)
    {
        SDL_Surface *surface = TTF_RenderText_Blended(Game::assets->getFont(font), text.c_str(), textColor);
        texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
        SDL_FreeSurface(surface);

        SDL_QueryTexture(texture, nullptr, nullptr, &position.w, &position.w);
    }

    void draw() override
    {
        SDL_RenderCopy(Game::renderer, texture, nullptr, &position);
    }
};