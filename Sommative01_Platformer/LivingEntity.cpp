#include "LivingEntity.h"
#include <SFML/Graphics.hpp>



LivingEntity::LivingEntity(const std::string& textures_folder, const float sprint_modifier, const float horizontal_max_speed)
{
	// Loading files as textures
	up_.loadFromFile(textures_folder + "/Up.png");
	down_.loadFromFile(textures_folder + "/Down.png");
	left_.loadFromFile(textures_folder + "/Left.png");
	right_.loadFromFile(textures_folder + "/Right.png");

	sprint_modifier_ = sprint_modifier;
	horizontal_max_speed_ = horizontal_max_speed;
	is_sprinting_ = false;

	SetSprite(right_);
	setOrigin(GetSprite().getGlobalBounds().width / 2, GetSprite().getGlobalBounds().height);
}