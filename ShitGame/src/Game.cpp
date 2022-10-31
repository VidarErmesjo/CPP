#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "AwesomeToolz.h"

Map *map;
Manager manager;

SDL_Window *Game::window = nullptr;
SDL_Renderer *Game::renderer = nullptr;
SDL_Rect Game::camera;
SDL_Event Game::event;
AssetManager *Game::assets = new AssetManager(&manager);
bool Game::isRunning = false;

auto &player(manager.addEntity());
auto &label(manager.addEntity());

Game::Game()
{
    std::cout << "Hello Game!" << std::endl;
}

Game::~Game()
{
    std::cout << "Goodbye Game!" << std::endl;
}

void Game::init(const char* title, uint16_t width, uint16_t height, bool fullscreen)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "SDL initialized ..." << std::endl;

        Game::camera = {0, 0, width, height};

        Game::window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::camera.w, Game::camera.h, (fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
        if(Game::window)
             std::cout << "Window created ..." << std::endl;

        Game::renderer = SDL_CreateRenderer(Game::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(Game::renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            std::cout << "Renderer created ..." << std::endl;
        }

        //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
        //SDL_ShowCursor(false);

        Game::isRunning = true;
    }
    else
        std::cout << "IMG_Init() HAS FAILED! SDL_ERROR: " << SDL_GetError() << std::endl;

    if(TTF_Init() == -1)
        std::cout << "TTF_Init() HAS FAILED! TTF_ERROR: " << TTF_GetError() << std::endl;
     
/////////////
    Game::assets->addFont("consola", "res/fonts/consola.ttf", 16);

    Game::assets->addTexture("terrain", "res/gfx/Terrain.png");
    Game::assets->addTexture("player", "res/gfx/Shitsprite_idle.png");
    Game::assets->addTexture("projectile", "res/gfx/Projectile.png");
    
    map = new Map("terrain", 2, 32);
    map->loadMap("res/maps/Terrain.map", 25, 20);

    player.addComponents<TransformComponent>(800.0f, 600.0f, 16, 16, 2);
    player.addComponents<SpriteComponent>("player", true);
    player.addComponents<ControllerComponent>();
    player.addComponents<ColliderComponent>("player");
    player.addGroup(groupPlayers);

    SDL_Color fontColor = {255, 255, 255, 255};
    label.addComponents<UILabel>(10, 10, "This is ShitGame!", "consola", fontColor);

    assets->createProjectile(Vector2D(500, 600), Vector2D(2, 0), 200, 2, "projectile");
}

auto &tiles(manager.getGroup(Game::groupMap));
auto &players(manager.getGroup(Game::groupPlayers));
auto &colliders(manager.getGroup(Game::groupColliders));
//auto &npcs(manager.getGroup(Game::groupNPCs));
//auto &enemies(manager.getGroup(Game::groupEnemies));
auto &projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents()
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            Game::isRunning = false;
    }
}

void Game::update()
{
    SDL_Rect playerCollider = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPosition = player.getComponent<TransformComponent>().position;
    
    std::stringstream stringStream;
    stringStream << playerPosition;
    label.getComponent<UILabel>().setLabelText(stringStream.str(), "consola");

    manager.refresh();
    manager.update();

    for(auto &collider : colliders)
    {
        SDL_Rect colliderCollider = collider->getComponent<ColliderComponent>().collider;
        if(Collision::AABB(playerCollider, colliderCollider))
            player.getComponent<TransformComponent>().position = playerPosition;
    }

    for(auto &projectile : projectiles)
    {
        SDL_Rect projectileCollider = projectile->getComponent<ColliderComponent>().collider;
        if(Collision::AABB(playerCollider, projectileCollider))
        {
            projectile->destroy();
            std::cout << "Hit player!" << std::endl;
        }
    }

    camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - camera.w / 2);
    camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - camera.h / 2);

    if(camera.x < 0)
        camera.x = 0;
    else if(camera.x > camera.w)
        camera.x = camera.w;

    if(camera.y < 0)
        camera.y = 0;
    else if(camera.y > camera.h)
        camera.y = camera.h;
}

void Game::render()
{
    SDL_RenderClear(renderer);
 
    for(auto &tile : tiles)
        tile->draw();

    for(auto &collider : colliders)
        collider->draw();

    for(auto &player : players)
        player->draw();

    /*for(auto &npc : npcs)
        npc->draw();*/
    
    /*for(auto &enemy : enemies)
        enemy->draw();*/

    for(auto &projectile : projectiles)
        projectile->draw();

    label.draw();

    // Helper:
    int w, h;
    SDL_QueryTexture(player.getComponent<SpriteComponent>().getTexture(), nullptr, nullptr, &w, &h);
    Vector2D origin = player.getComponent<TransformComponent>().position;
    origin.x += w/4 - camera.x;
    origin.y += h - camera.y;

    int x, y;
    if(SDL_GetMouseState(&x, &y) == 1)
    {
        int x0, y0;
        x0 = static_cast<int>(origin.x);
        y0 = static_cast<int>(origin.y);
        AwesomeToolz::infiniteGreenLaser(x0, y0);
        AwesomeToolz::finiteRedLaser(x0, y0);
        double cos = AwesomeToolz::calculateCos(x0, y0);
        double sin = AwesomeToolz::calculateSin(x0, y0);
        double r = std::sqrt(cos*cos + sin*sin);
        std::cout << "Angle:(" << cos << "," << sin << "," << r << ")" << std::endl;
    }

    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(Game::renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
    SDL_RenderDrawPoint(Game::renderer, x, y);
    SDL_SetRenderDrawColor(Game::renderer, r, g, b, a);

    /*std::cout << "Player:(" << w << "," << h << ")";
    std::cout << ", Camera:(" << Game::camera.x << "," << Game::camera.y << ")";
    std::cout << ", Mouse:(" << x << "," << y << ")" << std::endl;*/

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    // Destroy font!
    TTF_Quit();
    SDL_DestroyWindow(Game::window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
    std::cout << "Game cleaned ..." << std::endl;
}