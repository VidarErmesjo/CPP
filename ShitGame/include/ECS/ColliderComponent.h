#pragma once
#include <string>
#include <SDL2/SDL.h>

#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component
{
public:
    SDL_Rect collider;
    std::string tag;

    SDL_Texture *texture;
    SDL_Rect source, destination;

    TransformComponent *transform;

    ColliderComponent(std::string tag)
    : tag(tag)
    {}

    ColliderComponent(std::string tag, int x, int y, int size)
    : tag(tag)
    {
        collider.x = x;
        collider.y = y;
        collider.h = collider.w = size;
    }

    void init() override
    {
        if(!entity->hasComponent<TransformComponent>())
            entity->addComponents<TransformComponent>();

        transform = &entity->getComponent<TransformComponent>();

        texture = TextureManager::loadTexture("res/gfx/Collider.png");
        source = {0, 0, 32, 32};
        destination = {collider.x, collider.y, collider.w, collider.h};
    }

    void update() override
    {
        if(tag != "terrain")
        {
            collider.x = (int) transform->position.x;
            collider.y = (int) transform->position.y;
            collider.w = transform->w * transform->scale;
            collider.h = transform->h * transform->scale;
        }

        destination.x = collider.x - Game::camera.x;
        destination.y = collider.y - Game::camera.y;
    }

    void draw() override
    {
        TextureManager::draw(texture, source, destination, SDL_FLIP_NONE);
    }
};