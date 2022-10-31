#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class ColliderComponent;
class AssetManager;

class Game
{
    int cnt = 0;

public:
    static SDL_Window *window;
    static SDL_Renderer *renderer;
    static SDL_Rect camera;
    static SDL_Event event;
    static AssetManager *assets;
    static bool isRunning;

    enum groupLabels : std::size_t
    {
        groupMap,
        groupPlayers,
        //groupNPCs,
        //groupEnemies,
        groupColliders,
        groupProjectiles
    };

    Game();
    ~Game();

    void init(const char* title, uint16_t width, uint16_t height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; }
};