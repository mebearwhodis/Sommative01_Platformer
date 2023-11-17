#pragma once
#include "Tile.h"
#include <SFML/Graphics.hpp>

class Texture
{
    Texture() = delete;  // Deleting the constructor to prevent instantiation
    static sf::Texture empty_;
    static sf::Texture dirt_;
    static sf::Texture grass_;
    static sf::Texture start_;
    static sf::Texture end_;

    static sf::Texture background_texture_;

    static std::map<TileType, sf::Texture> type_to_texture_;

public:
    static void LoadTextures();

    static sf::Texture GetEmptyTexture() { return empty_; }
    static sf::Texture GetDirtTexture() { return dirt_; }
    static sf::Texture GetGrassTexture() { return grass_; }
    static sf::Texture GetStartTexture() { return start_; }
    static sf::Texture GetEndTexture() { return end_; }
    static sf::Texture GetBackgroundTexture() { return background_texture_; }

    static sf::Texture GetTextureFromType(TileType t) { return type_to_texture_.at(t); }
};
