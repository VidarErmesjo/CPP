#pragma once
#include <string>
#include <fstream>

#include "Game.h"
#include "ECS/Components.h"

class Map
{
    std::string textureId;
    int mapScale;
    int tileSize;
    int scaledSize;

public:
    Map(std::string id, int scale, int size);
    ~Map();

    void loadMap(std::string path, int w, int h);
    void addTile(int x0, int y0, int x, int y);
};