#pragma once
#include "EntityComponentSystem.h"
#include "Components.h"
#include "../Game.h"

class ControllerComponent : public Component
{
    TransformComponent *transform;
    SpriteComponent *sprite;

public:
    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override
    {
        //int x, y;
        //const Uint32 mouseState = SDL_GetMouseState(&x, &y);
        const Uint8 *keyboardState = SDL_GetKeyboardState(nullptr);

        if(keyboardState[SDL_SCANCODE_ESCAPE])
            Game::isRunning = false;
        //if(keyboardState[SDL_SCANCODE_F11])
            // Toggle fullscreen

        transform->velocity.zero();
        sprite->play("Idle");        
        if(keyboardState[SDL_SCANCODE_W])
        {
            transform->velocity.y = -1.0f;
            sprite->play("Walk");
        }
        if(keyboardState[SDL_SCANCODE_A])
        {
            transform->velocity.x = -1.0f;
            sprite->play("Walk");
            sprite->spriteFlip = SDL_FLIP_NONE;
        }
        if(keyboardState[SDL_SCANCODE_S])
        {
            transform->velocity.y = 1.0f;
            sprite->play("Walk");
        }
        if(keyboardState[SDL_SCANCODE_D])
        {
            transform->velocity.x = 1.0f;
            sprite->play("Walk");
            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
        }
    }
};