#pragma once
#include "Tile.h"
#include <SFML/Graphics.hpp>

class Texture
{
	sf::Texture empty_;
	sf::Texture dirt_;
	sf::Texture grass_;
    sf::Texture start_;
    sf::Texture end_;

    sf::Texture background_texture_;

    std::map<TileType, sf::Texture> type_to_texture_{ {TileType::kEmpty, empty_}, {TileType::kEmptySolid, empty_}, {TileType::kGrass, grass_}, {TileType::kDirt, dirt_} };

public:
    void LoadTextures();

    //sf::Texture GetEmptyTexture() { return empty_; }
    //sf::Texture GetDirtTexture() { return dirt_; }
    //sf::Texture GetGrassTexture() { return grass_; }
    //sf::Texture GetStartTexture() { return start_; }
    //sf::Texture GetEndTexture() { return end_; }
    sf::Texture GetBackgroundTexture() { return background_texture_; }

    sf::Texture GetTextureFromType(const TileType t) { return type_to_texture_.at(t); }
};
