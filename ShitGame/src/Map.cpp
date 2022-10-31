#include "Map.h"

extern Manager manager;

Map::Map(std::string id, int scale, int size)
:   textureId(id), mapScale(scale), tileSize(size), scaledSize(scale * size)
{}

Map::~Map()
{
}

void Map::loadMap(std::string path, int w, int h)
{
    char tile;
    std::fstream file;
    file.open(path);

    int x, y;
    for(int row = 0; row < h; row++)
    {
        for(int col = 0; col < w; col++)
        {
            file.get(tile);
            y = atoi(&tile) * tileSize;
            file.get(tile);
            x = atoi(&tile) * tileSize;
            addTile(x, y, col * scaledSize, row * scaledSize);
            file.ignore();
        }
    }

    file.ignore();

    for(int row = 0; row < h; row++)
    {
        for(int col = 0; col < w; col++)
        {
            file.get(tile);
            if(tile == '1')
            {
                auto &collider(manager.addEntity());
                collider.addComponents<ColliderComponent>("terrain", col * scaledSize, row * scaledSize, scaledSize);
                collider.addGroup(Game::groupColliders);
            }
            file.ignore();
        }
    }

    file.close();
}

void Map::addTile(int x0, int y0, int x, int y)
{
    auto& tile(manager.addEntity());
    tile.addComponents<TileComponent>(x0, y0, x, y, tileSize, mapScale, textureId);
    tile.addGroup(Game::groupMap);
}

/*void Map::loadMap(const char *path)
{
    std::string line;
    std::ifstream file;

    uint16_t tilesWide, tilesHigh, tileWidth, tileHeight, layer;

    file.open(path);
    while(!file.eof())
    {
        file >> line;
        std::cout << line.c_str() << ": ";
        if(line.compare("tileswide") == 0)
        {
            file >> line;
            std::cout << line.c_str() << std::endl;
            tilesWide = stoi(line);
        }

        file >> line;
        std::cout << line.c_str() << ": ";
        if(line.compare("tileshigh") == 0)
        {
            file >> line;
            std::cout << line.c_str() << std::endl;
            tilesHigh = stoi(line);
        }

        file >> line;
        std::cout << line.c_str() << ": ";
        if(line.compare("tilewidth") == 0)
        {
            file >> line;
            std::cout << line.c_str() << std::endl;
            tileWidth = stoi(line);
        }

        file >> line;
        std::cout << line.c_str() << ": ";
        if(line.compare("tileheight") == 0)
        {
            file >> line;
            std::cout << line.c_str() << std::endl;
            tileHeight = stoi(line);
        }

        file >> line;
        std::cout << line.c_str() << ": ";
        if(line.compare("layer") == 0)
        {
            file >> line;
            std::cout << line.c_str() << std::endl;
            layer = stoi(line);
        }

        uint16_t x, y = 0;
        while(file >> line)
        {
            x = 0;
            for(const char &tile : line)
            {
                if(tile != ',')
                {
                    std::cout << atoi(&tile);
                    Game::AddTile(atoi(&tile), x * tileWidth, y * tileHeight, tileWidth, tileHeight);
                    x++;
                }
            }
            std::cout << std::endl;
            y++;
        }
    }

    file.close();
}*/