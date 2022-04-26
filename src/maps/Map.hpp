#pragma once

#include <SDL2/SDL.h>

class Map {
    public:
        float map[1000][1000] = {{0}};

        Map();
        ~Map();
        
        void draw();

    private:
        SDL_Rect src, dst;

        SDL_Texture *forest;
        SDL_Texture *grass;
        SDL_Texture *ocean;
        SDL_Texture *rock;
        SDL_Texture *sand;
        SDL_Texture *snow;
        SDL_Texture *shore;
        SDL_Texture *trench;
        SDL_Texture *tree;
};