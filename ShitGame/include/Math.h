#pragma once

#include <iostream>
#include <cmath>

struct Vector2f
{
    Vector2f()
    :x(0.0f), y(0.0f)
    {}

    Vector2f(double x, double y)
    : x(x), y(y)
    {}

    void print()
    {
        std::cout << "[" << std::to_string(x) << ", " << std::to_string(y) << "]" << std::endl;
    }

    double x, y;
};