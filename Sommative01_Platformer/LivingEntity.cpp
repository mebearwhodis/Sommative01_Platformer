#include "LivingEntity.h"
#include <SFML/Graphics.hpp>



LivingEntity::LivingEntity(const std::string& textures_folder, const float sprint_modifier, const float horizontal_max_speed)
{
	sf::Texture temp_texture;
	// Loading files as textures
	temp_texture.loadFromFile(textures_folder + "/Left.png");
	left_.push_back(temp_texture);
	temp_texture.loadFromFile(textures_folder + "/Left2.png");
	left_.push_back(temp_texture);
	temp_texture.loadFromFile(textures_folder + "/Right.png");
	right_.push_back(temp_texture);
	temp_texture.loadFromFile(textures_folder + "/Right2.png");
	right_.push_back(temp_texture);
	jump_r_.loadFromFile(textures_folder + "/Jump.png");
	jump_l_.loadFromFile(textures_folder + "/JumpL.png");
	still_r_.loadFromFile(textures_folder + "/Still.png");
	still_l_.loadFromFile(textures_folder + "/StillL.png");

	sprint_modifier_ = sprint_modifier;
	horizontal_max_speed_ = horizontal_max_speed;
	is_sprinting_ = false;

	SetSprite(still_r_);
	this->sprite_.setOrigin(0, -0.5f*GetSprite().getGlobalBounds().height);
	setOrigin(GetSprite().getGlobalBounds().width / 2, GetSprite().getGlobalBounds().height);
}