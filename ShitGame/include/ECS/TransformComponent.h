#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{
public:
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;

    int w, h, scale, speed = 2;
    TransformComponent()
    : w(16), h(16), scale(1)
    {
        //position.zero();
        position.center();
    }

    TransformComponent(uint16_t scale)
    :   w(16), h(16), scale(scale)
    {
        position.center();
    }

    TransformComponent(double x, double y)
    :   w(16), h(16)
    {
        position.zero();
    }

    TransformComponent(double x, double y, uint16_t w, uint16_t h)
    :   w(w), h(h), scale(1)
    {
        position.x = x;
        position.y = y;
    }

    TransformComponent(double x, double y, uint16_t w, uint16_t h, uint16_t scale)
    :   w(w), h(h), scale(scale)
    {
        position.x = x;
        position.y = y;
    }

    void init() override
    {
        velocity.zero();
        acceleration.zero();
    }

    void update() override
    {
        position.x += velocity.x * speed; //acceleration.x;
        position.y += velocity.y * speed; //acceleration.y;
    }
};