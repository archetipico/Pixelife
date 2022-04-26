#include "Game.hpp"

#define FPS 60

Game *game = nullptr;

int main(int argc, char *argv[]) {
    const int FRAME_DELAY = 1000 / FPS;

    Uint32 start, time;
    game = new Game("Pixelife", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, false);
    
    while (game->getRun()) {
        start = SDL_GetTicks();

        game->handle();
        game->update();
        game->render();

        time = SDL_GetTicks() - start;
        if (FRAME_DELAY > time) {
            SDL_Delay(FRAME_DELAY - time);
        }
    }

    return 0;
}