#include "LivingEntity.h"
#include <SFML/Graphics.hpp>



LivingEntity::LivingEntity(const std::string& textures_folder, const float sprint_modifier, const float horizontal_max_speed)
{
	// Loading files as textures
	left_.loadFromFile(textures_folder + "/Left.png");
	right_.loadFromFile(textures_folder + "/Right.png");

	sprint_modifier_ = sprint_modifier;
	horizontal_max_speed_ = horizontal_max_speed;
	is_sprinting_ = false;

	SetSprite(right_);
	this->sprite_.setOrigin(0, -0.5f*GetSprite().getGlobalBounds().height);
	setOrigin(GetSprite().getGlobalBounds().width / 2, GetSprite().getGlobalBounds().height);
}