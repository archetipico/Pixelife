#include "Game.hpp"
#include "objects/GameObject.hpp"
#include "maps/Map.hpp"
#include "maps/MapNoise.hpp"
#include "textures/TextureManager.hpp"

GameObject *player = nullptr;
GameObject *enemy = nullptr;
Map *map = nullptr;
MapNoise *noise = nullptr;
SDL_Renderer *Game::renderer = nullptr;

/* Construct game with title, position on screen, width, height and fullscreen */
Game::Game(const char *title, int x, int y, int w, int h, bool fscreen) {
    int fscreenFlag = fscreen ? SDL_WINDOW_FULLSCREEN : 0;
    
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Initialization" << std::endl;
        
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, fscreenFlag);
        std::string out = window ? "Window OK" : "WINDOW FAILED";
        std::cout << out << std::endl;

        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        out = window ? "Renderer OK" : "RENDERER FAILED";
        std::cout << out << std::endl;

        setRun(true);
    }

    map = new Map();
    noise = new MapNoise(map);
    noise->generate();

    //player = new GameObject("src/textures/assets/player.png", 0, 0);
    //enemy = new GameObject("src/textures/assets/enemy.png", 50, 50);
}

/* Destruct game */
Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    window = nullptr;
    renderer = nullptr;
}

/* Handle game events */
void Game::handle() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            quit();
            break;
        default:
            break;
    }
}

/* Quit game */
void Game::quit() {
    setRun(false);    
    SDL_Quit();

    std::cout << "Goodbye" << std::endl;
}

/* Render on screen */
void Game::render() {
    SDL_RenderClear(renderer);

    map->draw();
    //noise = new MapNoise(map);
    //noise->generate();
    //player->render();
    //enemy->render();

    SDL_RenderPresent(renderer);
}

/* Update game objects */
void Game::update() {
    //player->update();
    //enemy->update();
}

/* Get if the game is running */
bool Game::getRun() {
    return run;
}

/* Set game running status */
void Game::setRun(bool val) {
    run = val;
}