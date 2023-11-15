#pragma once
#include "LivingEntity.h"

class Player : public LivingEntity
{
	sf::Vector2f player_size_;
	//sf::Vector2f player_pos_;
	sf::Vector2f player_speed_;
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
	void ResetPosition(const sf::Vector2f respawn_point);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		// You can DrawLevel other high-level objects
		states.transform = getTransform();
		target.draw(sprite_, states);
	}
};

