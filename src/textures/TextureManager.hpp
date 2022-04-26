#pragma once

#include <fstream>

#include "../Game.hpp"

class TextureManager {
    public:
        static void draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst);
        static SDL_Texture *load(const char *file);
};