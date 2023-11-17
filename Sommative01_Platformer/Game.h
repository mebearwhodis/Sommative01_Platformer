#pragma once
#include <SFML/Graphics.hpp>

#include "Level.h"
#include "Player.h"
#include "Texture.h"

class Game
{
	//Physics
	sf::Vector2f gravity_force_ = sf::Vector2f(0, 0.f);

	//Tiles & Collisions
	sf::RectangleShape base_tile_;
	sf::RectangleShape hovered_tile_;
	sf::RectangleShape debug_limit_shape_vertical_;
	sf::RectangleShape debug_limit_shape_horizontal_;

	//Player
	Player player_;

public:

	Game() : player_("data/sprites/player", 1.2f, 3.f) {}


	//Window
	sf::RenderWindow window_;
	sf::View view_;

	void init();
	void update();
};



