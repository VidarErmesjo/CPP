#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.h"

class TextureManager
{
public:
    static SDL_Texture *loadTexture(const char* path);
    static void draw(SDL_Texture *texture, SDL_Rect source, SDL_Rect destination, SDL_RendererFlip renderFlip);
};