#pragma once
#include "EntityComponentSystem.h"
#include "Components.h"
#include "../Vector2D.h"

class ProjectileComponent : public Component
{
    TransformComponent *transform;
    Vector2D velocity;

    int range = 0;
    int speed = 0;
    int distance = 0;

public:
    ProjectileComponent(int range, int speed, Vector2D velocity)
    :   velocity(velocity), range(range), speed(speed)
    {}
    ~ProjectileComponent()
    {}

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        transform->velocity = velocity;
    }

    void update() override
    {
        distance += speed;

        if(distance > range)
        {
            entity->destroy();
            std::cout << "Out of range!" << std::endl;
        }
        else if(transform->position.x > Game::camera.x + Game::camera.w ||
                transform->position.x < Game::camera.x ||
                transform->position.y > Game::camera.y + Game::camera.h ||
                transform->position.y < Game::camera.y)
        {
            entity->destroy();
            std::cout << "Out of bounds!" << std::endl;
        }
    }
};