#include "Map.hpp"
#include "../Game.hpp"
#include "../textures/TextureManager.hpp"

#define SIZE 2

/* Load map textures and settings */
Map::Map() {
    forest = TextureManager::load("src/textures/assets/forest.png");
    grass = TextureManager::load("src/textures/assets/grass.png");
    ocean = TextureManager::load("src/textures/assets/ocean.png");
    rock = TextureManager::load("src/textures/assets/rock.png");
    sand = TextureManager::load("src/textures/assets/sand.png");
    snow = TextureManager::load("src/textures/assets/snow.png");
    shore = TextureManager::load("src/textures/assets/shore.png");
    trench = TextureManager::load("src/textures/assets/trench.png");
    tree = TextureManager::load("src/textures/assets/tree.png");

    src.x = src.y = 0;
    dst.x = dst.y = 0;

    src.w = dst.w = SIZE;
    src.h = dst.h = SIZE;
}

/* Destroy map */
Map::~Map() {
    SDL_DestroyTexture(forest);
    SDL_DestroyTexture(grass);
    SDL_DestroyTexture(ocean);
    SDL_DestroyTexture(rock);
    SDL_DestroyTexture(sand);
    SDL_DestroyTexture(snow);
    SDL_DestroyTexture(shore);
    SDL_DestroyTexture(trench);
    SDL_DestroyTexture(tree);

    forest = nullptr;
    grass = nullptr;
    ocean = nullptr;
    rock = nullptr;
    sand = nullptr;
    snow = nullptr;
    shore = nullptr;
    trench = nullptr;
    tree = nullptr;
}

/* Draw texture based on values on map */
void Map::draw() {
    float type = 0;

    for (int row = 0; row < 1000; row++) {
        for (int col = 0; col < 1000; col++) {
            type = map[row][col];

            dst.x = col * SIZE;
            dst.y = row * SIZE;
            
            if (type < 0.005) {
                TextureManager::draw(trench, src, dst);
            } else if (type >= 0.005 && type < 0.05) {
                TextureManager::draw(ocean, src, dst);
            } else if (type >= 0.05 && type < 0.07) {
                TextureManager::draw(shore, src, dst);
            } else if (type >= 0.07 && type < 0.09) {
                TextureManager::draw(sand, src, dst);
            } else if (type >= 0.09 && type < 0.11) {
                TextureManager::draw(grass, src, dst);
            } else if (type >= 0.11 && type < 0.2) {
                TextureManager::draw(forest, src, dst);
            } else if (type >= 0.2 && type < 0.4) {
                TextureManager::draw(rock, src, dst);
            } else if (type == 1) {
                TextureManager::draw(tree, src, dst);
            } else {
                TextureManager::draw(snow, src, dst);
            }
        }
    }
}
