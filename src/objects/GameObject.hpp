#pragma once

#include "../Game.hpp"

class GameObject {
    public:
        GameObject(const char *file, int x, int y);
        ~GameObject();

        void render();
        void update();

    private:
        int x, y;
        SDL_Texture *tex;
        SDL_Rect src, dst;
};