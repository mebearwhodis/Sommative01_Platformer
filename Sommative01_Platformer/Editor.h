#pragma once
#include "Tile.h"
#include <SFML/Graphics.hpp>

#include "Level.h"
#include "Texture.h"

class Editor
{
	//Tiles
	sf::RectangleShape base_tile_;
	sf::RectangleShape hovered_tile_;

	TileType selected_tile_type_ = TileType::kGrass;

public:
	//Window
	sf::RenderWindow window_;
	sf::View view_;

	void init();
	//sf::RenderWindow GetWindow() { return window_; } -Not working, deleted function error?
	void update(const Level& level);
};

