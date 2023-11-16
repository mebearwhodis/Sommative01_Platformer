#include "Player.h"


Player::Player(const std::string& textures_folder, const float sprint_modifier, const float horizontal_max_speed) : LivingEntity(textures_folder, sprint_modifier, horizontal_max_speed)
{
	//LivingEntity::LivingEntity(); //call back to parent constructor

	player_size_ = sf::Vector2f(30, 30);

	player_speed_ = sf::Vector2f(0, 0);
	player_velocity_ = sf::Vector2f(0, 0);
	jump_force_ = sf::Vector2f(0, 0);
	move_force_ = sf::Vector2f(0, 0);

	grounded_ = false;
}

void Player::ResetPosition(const sf::Vector2f respawn_point)
{
	setPosition(respawn_point);
	//player_pos_ = respawn_point;
	player_velocity_ = sf::Vector2f(0, 0);
}
