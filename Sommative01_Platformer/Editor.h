#pragma once
#include "Tile.h"
#include <SFML/Graphics.hpp>
#include "Texture.h"

class Editor
{
public:

	//Tiles
	sf::RectangleShape base_tile_;
	sf::RectangleShape hovered_tile_;

	//Type of thing to add (Tile/Interactable)
	bool stamp_type_ = true;

	Tile selected_tile_ = {TileType::kEmpty, false, false};
	Interactive selected_interact_ = {InteractiveType::kEmpty, false, false, false };
	//Window
	sf::RenderWindow window_;
	sf::View view_;


	sf::Sprite background_sprite_;

	sf::Sprite GetBackgroundSprite() { return background_sprite_; }
	void SetBackgroundSprite(const sf::Texture& texture) { background_sprite_.setTexture(texture); }
	void SetBackgroundOrigin(const sf::Vector2f origin) { background_sprite_.setOrigin(origin); }
	void SetBackgroundPosition(const sf::Vector2f position) { background_sprite_.setPosition(position); }


	void init();
	//sf::RenderWindow GetWindow() { return window_; } -Not working, deleted function error?
	void update();
};

