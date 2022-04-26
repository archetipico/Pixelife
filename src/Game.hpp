#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Game {
    public:
        Game(const char *title, int x, int y, int w, int h, bool fscreen);
        ~Game();
        
        void handle();
        void quit();   
        void render();
        void update();

        bool getRun();
        void setRun(bool val);

        static SDL_Renderer *renderer;
    
    private:
        int count = 0;
        bool run = false;
        SDL_Window *window;
};