#include "LivingEntity.h"
#include <SFML/Graphics.hpp>



void LivingEntity::LoadEntity(const std::string& textures_folder)
{
	// Loading files as textures
	up_.loadFromFile(textures_folder + "/Up.png");
	down_.loadFromFile(textures_folder + "/Down.png");
	left_.loadFromFile(textures_folder + "/Left.png");
	right_.loadFromFile(textures_folder + "/Right.png");

	SetSprite(right_);
	setOrigin(GetSprite().getGlobalBounds().width / 2, GetSprite().getGlobalBounds().height);
}