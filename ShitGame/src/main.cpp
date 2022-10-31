#include "Game.h"

int main(int argc, char* argv[])
{
    try
    {
        Game game;

        const Uint32 framesPerSecond = 120;
        const Uint32 frameDelay = 1000 / framesPerSecond;

        Uint32 frameStart;
        Uint32 frameTime;

        game.init("ShitGame", 1280, 720, false);

        while(game.running())
        {
            frameStart = SDL_GetTicks();

            game.handleEvents();
            game.update();
            game.render();

            frameTime = SDL_GetTicks() - frameStart;

            if(frameDelay > frameTime)
                SDL_Delay(frameDelay - frameTime);
        }

        game.clean();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}