#include "Player.h"


Player::Player(const std::string& textures_folder, const float sprint_modifier, const float horizontal_max_speed) : LivingEntity(textures_folder, sprint_modifier, horizontal_max_speed)
{
	player_size_ = sf::Vector2f(134, 190);

	player_speed_ = sf::Vector2f(5, 0);
	player_base_speed_ = sf::Vector2f(20, 0);
	player_velocity_ = sf::Vector2f(0, 0);
	jump_force_ = sf::Vector2f(0, 0);
	move_force_ = sf::Vector2f(1, 0);

	grounded_ = false;
}

void Player::ResetPosition(const sf::Vector2f respawn_point)
{
	setPosition(respawn_point);
	player_velocity_ = sf::Vector2f(0, 0);
}
