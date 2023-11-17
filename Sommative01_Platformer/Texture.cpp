#include "Texture.h"

// Definitions for static members

// Definitions for static members
sf::Texture Texture::empty_;
sf::Texture Texture::dirt_;
sf::Texture Texture::grass_;
sf::Texture Texture::start_;
sf::Texture Texture::end_;

sf::Texture Texture::background_texture_;

std::map<TileType, sf::Texture> Texture::type_to_texture_;
//{ {TileType::kEmpty, empty_}, {TileType::kEmptySolid, empty_}, {TileType::kGrass, grass_}, {TileType::kDirt, dirt_} }

void Texture::LoadTextures() {
    //empty_.loadFromFile("data/sprites/tiles/empty.png");
    grass_.loadFromFile("data/sprites/tiles/grassMid.png");
    dirt_.loadFromFile("data/sprites/tiles/grassCenter.png");
    background_texture_.loadFromFile("data/sprites/backgrounds/blue_desert.png");

    type_to_texture_ = {};
    type_to_texture_[TileType::kEmpty] = empty_;
    type_to_texture_[TileType::kEmptySolid] = empty_;
    type_to_texture_[TileType::kGrass] = grass_;
    type_to_texture_[TileType::kDirt] = dirt_;
    // Add other textures to the map similarly
}