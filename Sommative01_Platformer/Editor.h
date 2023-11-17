#pragma once
#include "Tile.h"
#include <SFML/Graphics.hpp>

#include "Level.h"
#include "Texture.h"

class Editor
{
public:
	//Tiles
	sf::RectangleShape base_tile_;
	sf::RectangleShape hovered_tile_;

	Tile selected_tile_ = {TileType::kEmpty, false, false};
	//Window
	sf::RenderWindow window_;
	sf::View view_;

	sf::Sprite background_sprite_;

	void init();
	//sf::RenderWindow GetWindow() { return window_; } -Not working, deleted function error?
	void update();
};

