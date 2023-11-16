#include "Texture.h"

// Definitions for static members

void Texture::LoadTextures() {
    empty_.loadFromFile("data/sprites/tiles/empty.png");
    grass_.loadFromFile("data/sprites/tiles/grassMid.png");
    dirt_.loadFromFile("data/sprites/tiles/grassCenter.png");
    background_texture_.loadFromFile("data/sprites/backgrounds/blue_desert.png");

    type_to_texture_[TileType::kEmpty] = empty_;
    type_to_texture_[TileType::kGrass] = grass_;
    type_to_texture_[TileType::kDirt] = dirt_;
    // Add other textures to the map similarly
}