#include "GameObject.hpp"
#include "../textures/TextureManager.hpp"

/* Assign position and texture to GameObject */
GameObject::GameObject(const char *file, int x, int y) {
    tex = TextureManager::load(file);
    this->x = x;
    this->y = y;
}

/* Destroy texture */
GameObject::~GameObject() {
    SDL_DestroyTexture(tex);
    tex = nullptr;
}

/* Render GameObject */
void GameObject::render() {
    SDL_RenderCopy(Game::renderer, tex, &src, &dst);
}

/* Update GameObject */
void GameObject::update() {
    x++;
    y++;

    src.w = 128;
    src.h = 128;
    src.x = 0;
    src.y = 0;

    dst.x = x;
    dst.y = y;
    dst.w = src.w * 2;
    dst.h = src.h * 2;
}