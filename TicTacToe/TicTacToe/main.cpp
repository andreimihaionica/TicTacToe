#include "Game.h"

int main(int argc, char* args[])
{
    // unused parameters
    (void)argc;
    (void)args;

    Game game;

    if (!game.initWindow())
    {
        std::cout << "Failed to initialize SDL" << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Event currentEvent;

    // game loop
    while (!game.getQuit())
    {
        // Handle events in queue (non-blocking)
        if (SDL_PollEvent(&currentEvent) != 0) {

            // process any event that has occurred
            game.processEvent(currentEvent);
        }

        // render the frame
        game.drawFrame();
    }

    game.destroyWindow();
    return 0;
}