#include "Vector2D.h"

Vector2D::Vector2D()
: x(0.0f), y(0.0f)
{}

Vector2D::Vector2D(double x, double y)
: x(x), y(y)
{}

Vector2D& Vector2D::Add(const Vector2D& vector)
{
    this->x += vector.x;
    this->y += vector.y;

    return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vector)
{
    this->x -= vector.x;
    this->y -= vector.y;

    return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vector)
{
    this->x *= vector.x;
    this->y *= vector.y;

    return* this;
}

Vector2D& Vector2D::Divide(const Vector2D& vector)
{
    this->x /= vector.x;
    this->y /= vector.y;

    return *this;
}

Vector2D& operator+(Vector2D& v1, Vector2D& v2)
{
    return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, Vector2D& v2)
{
    return v1.Subtract(v2);
}

Vector2D& operator*(Vector2D& v1, Vector2D& v2)
{
    return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, Vector2D& v2)
{
    return v1.Divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vector)
{
    return this->Add(vector);
}

Vector2D& Vector2D::operator-=(const Vector2D& vector)
{
    return this->Subtract(vector);
}

Vector2D& Vector2D::operator*=(const Vector2D& vector)
{
    return this->Multiply(vector);
}

Vector2D& Vector2D::operator/=(const Vector2D& vector)
{
    return this->Divide(vector);
}

Vector2D& Vector2D::operator*(const int& multiplier)
{
    this->x *= multiplier;
    this->y *= multiplier;

    return *this;
}

Vector2D& Vector2D::zero()
{
    this->x = 0;
    this->y = 0;

    return *this;
}

Vector2D& Vector2D::center()
{
    int w, h;
    SDL_GetWindowSize(Game::window, &w, &h);
    this->x = static_cast<double>(w / 2);
    this->y = static_cast<double>(h / 2);

    return *this;
}

std::ostream& operator<<(std::ostream& ostream, const Vector2D& vector)
{
    ostream << "()" << vector.x << "," << vector.y << ")";
    return ostream;
}