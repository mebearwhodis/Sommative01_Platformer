#pragma once
#include "Tile.h"
#include <SFML/Graphics.hpp>

class Editor
{
	//Window
	sf::RenderWindow window_;
	sf::View view_;

	//Tiles
	sf::RectangleShape base_tile_;
	sf::RectangleShape hovered_tile_;

	TileType selected_tile_type_ = TileType::kGrass;

public:
	void init();
	void update();
};

