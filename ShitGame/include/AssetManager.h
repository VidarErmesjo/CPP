#pragma once
#include <map>
#include <string>
#include <SDL2/SDL_ttf.h>

#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/EntityComponentSystem.h"

class AssetManager
{
    Manager *manager;
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;

public:
    AssetManager(Manager *manager);
    ~AssetManager();

    // Game objects
    void createProjectile(Vector2D position, Vector2D velocity, int range, int speed, std::string id);


    // Texture management
    void addTexture(std::string id, const char *path);
    SDL_Texture *getTexture(std::string id);

    void addFont(std::string id, const char *path, int fontSize);
    TTF_Font *getFont(std::string id);
};