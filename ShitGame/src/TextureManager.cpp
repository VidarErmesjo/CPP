#include "TextureManager.h"

SDL_Texture *TextureManager::loadTexture(const char *path)
{
    //if(path[0] == '\0')
    if(!*path)
        return nullptr;

    SDL_Surface *surface = IMG_Load(path);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);

    if(texture == nullptr)
    {
        std::cout << "Failed to load texture! [" << path << "]" << std::endl;
        return nullptr;
    }

    return texture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect destination, SDL_RendererFlip renderFlip)
{
    SDL_RenderCopyEx(Game::renderer, texture, &source, &destination, 0.0f, nullptr, renderFlip);
}

