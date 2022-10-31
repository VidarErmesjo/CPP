#pragma once
#include <cmath>
#include <SDL2/SDL.h>
#include "Game.h"

class AwesomeToolz
{
public:
    static double calculateSin(int &x0, int &y0);
    static double calculateCos(int &x0, int &y0);
    static double calculateSlope(int &x0, int &y0, int &x, int &y);
    static void finiteRedLaser(int &x0, int &y0);
    static void infiniteGreenLaser(int &x0, int &y0);
};