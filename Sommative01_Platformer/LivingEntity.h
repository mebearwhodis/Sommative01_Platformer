#pragma once
#include "Entity.h"

class LivingEntity : public Entity, public sf::Transformable
{
	sf::Texture up_;
	sf::Texture down_;
	sf::Texture left_;
	sf::Texture right_;

	//float base_speed_; //For other potential living entities, like monsters or moving NPCs
	float sprint_modifier_;
	float horizontal_max_speed_;

	bool is_sprinting_;

public:
	//Constructor
	explicit LivingEntity(const std::string& textures_folder, float sprint_modifier, float horizontal_max_speed);
	//void LoadEntity(const std::string& textures_folder);

	//Getters & Setters
	sf::Texture GetTextureUp() { return up_; }
	sf::Texture GetTextureDown() { return down_; }
	sf::Texture GetTextureLeft() { return left_; }
	sf::Texture GetTextureRight() { return right_; }
	float GetSprintModifier() const { return sprint_modifier_; }
	float GetHorizontalMaxSpeed() const { return horizontal_max_speed_; }
	bool GetSprintingState() const { return is_sprinting_; }
	void SetSprintingState(const bool sprint_state) { is_sprinting_ = sprint_state; }	
};

