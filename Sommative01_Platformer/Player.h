#pragma once
#include "LivingEntity.h"

class Player final : public LivingEntity
{
	sf::Vector2f player_size_;
	//sf::Vector2f player_pos_;
	sf::Vector2f player_speed_;
	sf::Vector2f player_base_speed_;
	sf::Vector2f player_velocity_;
	sf::Vector2f jump_force_;
	sf::Vector2f move_force_;

	bool grounded_;

	//TODO: Set a Move function here? Or maybe in Living Entity
	//void Move(const sf::Vector2f direction)
	//{
	//	if (direction.y < 0)
	//	{
	//		SetSprite(up_);
	//	}
	//	if (direction.y > 0)
	//	{
	//		SetSprite(down_);
	//	}
	//	if (direction.x < 0)
	//	{
	//		SetSprite(left_);
	//	}
	//	if (direction.x > 0)
	//	{
	//		SetSprite(right_);
	//	}

	//	sf::Vector2f position = this->getPosition();
	//	position += direction * (this->base_speed_) * (1 + static_cast<float>(is_sprinting_));

	//	this->setPosition(position);

	//}
public:

	sf::Vector2f GetPlayerSize() const { return player_size_; }

	sf::Vector2f GetPlayerSpeed() const { return player_speed_; }
	void SetPlayerSpeed(const sf::Vector2f player_speed) { player_speed_ = player_speed; }
	sf::Vector2f GetPlayerBaseSpeed() const { return player_base_speed_; }

	sf::Vector2f GetPlayerVelocity() const { return player_velocity_; }
	void SetPlayerVelocity(const sf::Vector2f player_velocity) { player_velocity_ = player_velocity; }
	sf::Vector2f GetJumpForce() const { return jump_force_; }
	void SetJumpForce(const sf::Vector2f jump_force) { jump_force_ = jump_force; }
	sf::Vector2f GetMoveForce() const { return move_force_; }
	void SetMoveForce(const sf::Vector2f move_force) { move_force_ = move_force; }
	bool GetGroundedValue() const { return grounded_; }
	void SetGroundedValue(const bool grounded_value) { grounded_ = grounded_value; }

	Player(const std::string& textures_folder, const float sprint_modifier, const float horizontal_max_speed);

	void ResetPosition(const sf::Vector2f respawn_point);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		// You can DrawLevel other high-level objects
		states.transform = getTransform();
		target.draw(sprite_, states);
	}
};

