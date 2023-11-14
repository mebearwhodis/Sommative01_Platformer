#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"

class Game
{
public:
	//Physics
	sf::Vector2f gravity_force_ = sf::Vector2f(0, 0.f);

	//Window
	sf::RenderWindow window_;
	sf::View view_;

	//Tiles & Collisions
	sf::RectangleShape base_tile_;
	sf::RectangleShape hovered_tile_;
	sf::RectangleShape debug_limit_shape_vertical_;
	sf::RectangleShape debug_limit_shape_horizontal_;

	//Player
	Player player_;

	void init();
	void update();
};



