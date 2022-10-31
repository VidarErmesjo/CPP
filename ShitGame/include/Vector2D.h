#pragma once
#include <iostream>
#include <SDL2/SDL.h>

#include "Game.h"

struct Vector2D
{
    double x, y;

    Vector2D();
    Vector2D(double x, double y);

    Vector2D& Add(const Vector2D& vector);
    Vector2D& Subtract(const Vector2D& vector);
    Vector2D& Multiply(const Vector2D& vector);
    Vector2D& Divide(const Vector2D& vector);

    friend Vector2D& operator+(Vector2D& v1, Vector2D& v2);
    friend Vector2D& operator-(Vector2D& v1, Vector2D& v2);
    friend Vector2D& operator*(Vector2D& v1, Vector2D& v2);
    friend Vector2D& operator/(Vector2D& v1, Vector2D& v2);

    Vector2D& operator+=(const Vector2D& vector);
    Vector2D& operator-=(const Vector2D& vector);
    Vector2D& operator*=(const Vector2D& vector);
    Vector2D& operator/=(const Vector2D& vector);

    Vector2D& operator*(const int& multiplier);
    Vector2D& zero();
    Vector2D& center();

    friend std::ostream& operator<<(std::ostream& ostream, const Vector2D& vector);
};