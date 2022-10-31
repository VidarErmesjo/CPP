#pragma once
#include <map>
#include <SDL2/SDL.h>

#include "Components.h"
#include "Animation.h"
#include "../TextureManager.h"
#include "../AssetManager.h"

class SpriteComponent : public Component
{
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect source, destination;

    bool animated = false;
    uint16_t frames = 0u;
    uint16_t speed = 100u;

public:
    int animationIndex = 0;
    std::map<const char*, Animation> animations; 

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;
    SpriteComponent(std::string id)
    {
        setTexture(id);
    }

    SpriteComponent(std::string id, bool isAnimated)
    : animated(isAnimated), frames(0), speed(0)
    {
        Animation idle = Animation(0, 4, 200);
        Animation walk = Animation(0, 4, 100);

        animations.emplace("Idle", idle);
        animations.emplace("Walk", walk);

        play("Idle");

        setTexture(id);
    }

    ~SpriteComponent()
    {}

    void setTexture(std::string id)
    {
        texture = Game::assets->getTexture(id);
    }

    SDL_Texture *getTexture()
    {
        return texture;
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        source.x = source.y = 0;
        source.w = transform->w;
        source.h = transform->h;
    }

    void update() override
    {
        if(animated)
        {
            source.x = source.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }

        source.y = animationIndex * transform->h;

        destination.x = static_cast<int>(transform->position.x) - Game::camera.x;
        destination.y = static_cast<int>(transform->position.y) - Game::camera.y;
        destination.w = transform->w * transform->scale;
        destination.h = transform->h * transform->scale;
    }

    void draw() override
    {
        TextureManager::draw(texture, source, destination, spriteFlip);
    }

    void play(const char *animationName)
    {
        frames = animations[animationName].frames;
        animationIndex = animations[animationName].index;
        speed = animations[animationName].speed;
    }
};