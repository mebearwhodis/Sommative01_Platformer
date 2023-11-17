#pragma once
#include <SFML/Graphics.hpp>

#include "Level.h"
#include "Player.h"
#include "Texture.h"

class Game
{
public:
	//Physics
	sf::Vector2f gravity_force_ = sf::Vector2f(0, 0.f);

	//Tiles & Collisions
	sf::RectangleShape base_tile_;
	sf::RectangleShape hovered_tile_;
	sf::RectangleShape debug_limit_shape_vertical_;
	sf::RectangleShape debug_limit_shape_horizontal_;

	sf::Sprite background_sprite_;

	//Player
	Player player_;


	Game() : player_("data/sprites/player", 1.2f, 3.f) {}


	//Window
	sf::RenderWindow window_;
	sf::View view_;



	sf::Sprite GetBackgroundSprite() { return background_sprite_; }
	void SetBackgroundSprite(const sf::Texture& texture) { background_sprite_.setTexture(texture); }
	void SetBackgroundOrigin(const sf::Vector2f origin) { background_sprite_.setOrigin(origin); }
	void SetBackgroundPosition(const sf::Vector2f position) { background_sprite_.setPosition(position); }

	void init();
	void update();
};



