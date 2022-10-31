#include "AwesomeToolz.h"

double AwesomeToolz::calculateSin(int &x0, int &y0)
{
    int x, y;
    int flip = 1;
    SDL_GetMouseState(&x, &y);

    flip = ((y > y0 && x > x0) || (y < y0 && x <= x0)) ? -1 : flip;
        //flip *= -1;

    x -= x0;
    y -= y0;

    double angle = x / std::sqrt(x*x + y*y);
    angle = (angle > 0) ? 1 - angle : -1 - angle;
    return angle * flip;
}

double AwesomeToolz::calculateCos(int &x0, int &y0)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    x -= x0;
    y -= y0;

    double angle = x / std::sqrt(x*x + y*y);
    return angle;
}

double AwesomeToolz::calculateSlope(int &x0, int &y0, int &x, int &y)
{
    double deltaX, deltaY, slope = 0.0f;

    deltaX = 0.0f - (x - x0);
    deltaY = 0.0f - (y - y0);

    if(!deltaX == 0)
        slope = deltaY / deltaX;

    return slope;
}

void AwesomeToolz::finiteRedLaser(int &x0, int &y0)
{
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(Game::renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);

    int x, y;
    SDL_GetMouseState(&x, &y);

    SDL_RenderDrawLine(Game::renderer, x0, y0, x, y);
    SDL_SetRenderDrawColor(Game::renderer, r, g, b, a);
}

void AwesomeToolz::infiniteGreenLaser(int &x0, int &y0)
{
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(Game::renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);

    int x, y;
    SDL_GetMouseState(&x, &y);

    int x1 = (x < x0) ?
        0 : (y < Game::camera.h) ?
            Game::camera.w : 0;
    x1 = (x == x0) ? x0 : x1;

    int y1 = (x != x0) ?
        static_cast<int>(calculateSlope(x0, y0, x ,y) * (x1 - x0) + y0) : (y >= y0) ?
            Game::camera.h : 0;

    SDL_RenderDrawLine(Game::renderer, x0, y0, x1, y1);
    SDL_SetRenderDrawColor(Game::renderer, r, g, b, a);
}