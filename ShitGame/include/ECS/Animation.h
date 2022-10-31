#pragma once
#include <iostream>

struct Animation
{
    uint16_t index;
    uint16_t frames;
    uint16_t speed;

    Animation()
    {}
    Animation(uint16_t index, uint16_t frames, uint16_t speed)
    :   index(index), frames(frames), speed(speed)
    {}
};