#include "Player.h"

void Player::ResetPosition(const sf::Vector2f respawn_point)
{
	setPosition(respawn_point);
	//player_pos_ = respawn_point;
	player_velocity_ = sf::Vector2f(0, 0);
}

Player::Player()
{
	//sprite_;

	//up_;
	//down_;
	//left_;
	//right_;

	sprint_modifier_ = 1.3f;
	horizontal_max_speed_ = 1.0f;

	player_size_ = sf::Vector2f(30, 30);

	player_speed_ = sf::Vector2f(0,0);
	player_velocity_ = sf::Vector2f(0, 0);
	jump_force_ = sf::Vector2f(0, 0);
	move_force_ = sf::Vector2f(0, 0);

	is_sprinting_ = false;
	grounded_ = false;

}
