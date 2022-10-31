#pragma once
#include "EntityComponentSystem.h"
#include "../Game.h"
#include "../Vector2D.h"
#include "../TextureManager.h"


class TileComponent : public Component
{
public:

    SDL_Texture * texture;
    SDL_Rect source, destination;
    Vector2D position;

    TileComponent() = default;
    TileComponent(int x0, int y0, int x, int y, int size, int scale, std::string id)
    {
        texture = Game::assets->getTexture(id);
        
        position.x = static_cast<float>(x);
        position.y = static_cast<float>(y);

        source.x = x0;
        source.y = y0;
        source.w = source.h = size;

        destination.x = x;
        destination.y = y;
        destination.w = destination.h = size * scale;
    }

    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void update() override
    {
        destination.x = position.x - Game::camera.x;
        destination.y = position.y - Game::camera.y;
    }

    void draw() override
    {
        TextureManager::draw(texture, source, destination, SDL_FLIP_NONE);
    }
};
