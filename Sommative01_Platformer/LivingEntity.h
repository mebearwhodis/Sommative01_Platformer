#pragma once
#include "Entity.h"
#include <vector>

class LivingEntity : public Entity, public sf::Transformable
{
	//float base_speed_; //For other potential living entities, like monsters or moving NPCs
	float sprint_modifier_;
	float horizontal_max_speed_;

	bool is_sprinting_;

public:

	sf::Texture jump_r_;
	sf::Texture jump_l_;
	sf::Texture still_r_;
	sf::Texture still_l_;
	std::vector <sf::Texture> left_;
	std::vector <sf::Texture> right_;

	//Constructor
	explicit LivingEntity(const std::string& textures_folder, float sprint_modifier, float horizontal_max_speed);
	//void LoadEntity(const std::string& textures_folder);

	//Getters & Setters

	//TODO: Figure out getters for textures & sprites. I couldn't get them to work so I had to put them in public

	float GetSprintModifier() const { return sprint_modifier_; }
	float GetHorizontalMaxSpeed() const { return horizontal_max_speed_; }
	bool GetSprintingState() const { return is_sprinting_; }
	void SetSprintingState(const bool sprint_state) { is_sprinting_ = sprint_state; }	
};

