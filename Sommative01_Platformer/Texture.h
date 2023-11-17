#pragma once
#include "Tile.h"
#include <SFML/Graphics.hpp>

class Texture
{
public:
    static sf::Texture empty_;
    static sf::Texture dirt_;
    static sf::Texture grass_;
    static sf::Texture start_;
    static sf::Texture end_;

    static sf::Texture background_texture_;

    static std::map<TileType, sf::Texture> type_to_texture_;

    static void LoadTextures();

    //sf::Texture GetEmptyTexture() { return empty_; }
    //sf::Texture GetDirtTexture() { return dirt_; }
    //sf::Texture GetGrassTexture() { return grass_; }
    //sf::Texture GetStartTexture() { return start_; }
    //sf::Texture GetEndTexture() { return end_; }
    static sf::Texture GetBackgroundTexture() { return background_texture_; }

    static sf::Texture GetTextureFromType(const TileType t) { return type_to_texture_.at(t); }
};
