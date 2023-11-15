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
	void Sprint(const bool value) { is_sprinting_ = value; }
	void LoadEntity(const std::string& textures_folder);
};

