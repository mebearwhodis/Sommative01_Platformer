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

    std::map<TileType, sf::Texture> type_to_texture_;

public:
	void LoadTextures();
};

