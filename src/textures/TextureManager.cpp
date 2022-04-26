#include "TextureManager.hpp"

/* Draw texture to target */
void TextureManager::draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst) {
    SDL_RenderCopy(Game::renderer, tex, &src, &dst);
}

/* Load texture from file and return pointer to SDL_Texture */
SDL_Texture* TextureManager::load(const char *file) {
    std::ifstream exists(file);
    if (exists) {
        SDL_Surface *surf = IMG_Load(file);
        SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, surf);
        SDL_FreeSurface(surf);

        return tex;
    }
    
    std::cout << "TEXTURE " << file << " NOT FOUND" << std::endl;
    return nullptr;
}