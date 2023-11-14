#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable
{
protected:
	sf::Sprite sprite_;

public:
	sf::Sprite GetSprite() { return sprite_; }
	void SetSprite(const sf::Texture& texture) { sprite_.setTexture(texture); }
};

