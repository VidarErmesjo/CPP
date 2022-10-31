#include "AssetManager.h"
#include "ECS/Components.h"

AssetManager::AssetManager(Manager *manager)
:   manager(manager)
{}

AssetManager::~AssetManager()
{}

void AssetManager::createProjectile(Vector2D position, Vector2D velocity, int range, int speed, std::string id)
{
    auto &projectile(manager->addEntity());
    projectile.addComponents<TransformComponent>(position.x, position.y, 32, 32, 1);
    projectile.addComponents<SpriteComponent>(id, false);
    projectile.addComponents<ProjectileComponent>(range, speed, velocity);
    projectile.addComponents<ColliderComponent>(id);
    projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::addTexture(std::string id, const char *path)
{
    textures.emplace(id, TextureManager::loadTexture(path));
}

SDL_Texture *AssetManager::getTexture(std::string id)
{
    return textures[id];
}

void AssetManager::addFont(std::string id, const char *path, int fontSize)
{
    fonts.emplace(id, TTF_OpenFont(path, fontSize));
}

TTF_Font *AssetManager::getFont(std::string id)
{
    return fonts[id];
}