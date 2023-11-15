#include "Game.h"

#include <iostream>

#include "Level.h"
#include "Texture.h"


void Game::init()
{
	Texture::LoadTextures();
	Level::LoadLevelFromJson("levelOne.json");


	//selected_tile_ = Tile(TileType::kEmpty, false, false);
	//player_pos_ = Level::GetStartingPoint();

	// Set up the Window
	window_.create(sf::VideoMode(1600, 1200), "The Game");
	window_.setFramerateLimit(30);
	window_.setVerticalSyncEnabled(true);
	window_.setMouseCursorVisible(false);
	window_.setKeyRepeatEnabled(true);

	// Set up the View
	view_.setSize(1024, 1024);

	// Create Debug limit lines
	debug_limit_shape_vertical_.setSize(sf::Vector2f(2, 100000));
	debug_limit_shape_vertical_.setOrigin(1, 0);
	debug_limit_shape_vertical_.setFillColor(sf::Color(255, 0, 255));
	debug_limit_shape_horizontal_.setSize(sf::Vector2f(100000, 2));
	debug_limit_shape_horizontal_.setOrigin(0, 1);
	debug_limit_shape_horizontal_.setFillColor(sf::Color(255, 0, 255));

	//Create Player
	player_.LoadEntity("data/sprites/player");
	player_.ResetPosition(Level::GetRespawnPoint());

	//Create background
	Level::background_sprite_.setTexture(Texture::background_texture_);
	Level::background_sprite_.setOrigin(Level::background_sprite_.getGlobalBounds().width / 2, Level::background_sprite_.getGlobalBounds().height / 2);


}

void Game::update()
{
	sf::Event event;
	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window_.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			//TODO: Function to reset player position
			player_.ResetPosition(Level::GetRespawnPoint());
		}
	}
	window_.clear();
	float limit_x_low = -1000000000.f;
	float limit_x_high = 1000000000.f;
	float limit_y_low = -1000000000.f;
	float limit_y_high = 1000000000.f;

	//Reset the forces
	player_.jump_force_ = sf::Vector2f(0.0f, 0.0f);
	player_.move_force_ = sf::Vector2f(0.0f, 0.0f);

	Level::background_sprite_.setPosition(player_.getPosition().x, player_.getPosition().y);

	// Collision debug lines
	const sf::Vector2i player_coords = Level::PosToCoords(player_.getPosition());
	constexpr int margin = 1;

	if (Level::GetTileAt(player_coords + sf::Vector2i(1, 0)).solid_ || (player_coords + sf::Vector2i(1, 0)).x >= Level::GetLevelWidth()) {
		limit_x_high = (player_coords.x + 1) * TILE_SIZE - margin;
	}
	if (Level::GetTileAt(player_coords + sf::Vector2i(-1, 0)).solid_ || (player_coords + sf::Vector2i(-1, 0)).x < 0) {
		limit_x_low = (player_coords.x) * TILE_SIZE + margin;
	}
	if (Level::GetTileAt(player_coords + sf::Vector2i(0, 1)).solid_ || (player_coords + sf::Vector2i(0, 1)).y >= Level::GetLevelHeight()) {
		limit_y_high = (player_coords.y + 1) * TILE_SIZE - margin;
	}
	if (Level::GetTileAt(player_coords + sf::Vector2i(0, -1)).solid_ || (player_coords + sf::Vector2i(0, -1)).y < 0) {
		limit_y_low = (player_coords.y) * TILE_SIZE + margin;
	}



	//Movement - what will modify the speed vector

	//Sprint & Air Control
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		player_.Sprint(true);
	}
	else
	{
		player_.Sprint(false);
	}


	float speed_factor = player_.grounded_ ? 1.0f : 0.70f;
	if(player_.is_sprinting_)
	{
		speed_factor *= player_.sprint_modifier_;
	}

	//Left & Right
	sf::Vector2f delta(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player_.SetSprite(player_.left_);
		delta += sf::Vector2f(-1 * (player_.player_speed_.x) * speed_factor , 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player_.SetSprite(player_.right_);
		delta += sf::Vector2f((player_.player_speed_.x) * speed_factor, 0);
	}

	//Capping falling speed
	if (player_.player_speed_.y > 3)
	{
		player_.player_speed_.y = 3;
	}

	////Maybe use W/UP and S/Down for power-ups/moves (Floating, groundpound, ...)
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	//{
	//	player1.SetSprite(player1.up_);
	//	delta += sf::Vector2f(0, -player_base_speed_ * speed_factor);
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	//{
	//	player1.SetSprite(player1.down_);
	//	delta += sf::Vector2f(0, player_base_speed_ * speed_factor);
	//}

	//Forces - what will modify the acceleration vector
	//Player_velocity is a summ of forces

	//Jump higher if you press longer
	const bool jump_key_is_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	if (jump_key_is_down && player_.grounded_)
	{
		player_.jump_force_ = sf::Vector2f(0.0f, -35.0f);
	}
	player_.player_velocity_.y += jump_key_is_down ? 0.0f : 1.5f;

	if (!player_.grounded_)
	{
		player_.player_velocity_ += gravity_force_;
	}
	// Cancel vertical velocity if grounded
	else
	{
		player_.player_velocity_.y = 0;
	}

	player_.player_velocity_ += player_.jump_force_;
	player_.player_velocity_ += player_.move_force_;


	//Horizontal deceleration and acceleration
	player_.player_speed_ += player_.player_velocity_;
	if (!player_.grounded_)
	{
		player_.player_speed_.x *= 0.95f;
	}
	else
	{
		if (std::abs(player_.player_speed_.x) < 0.3)
		{
			player_.player_speed_.x = 0;
		}
		player_.player_speed_.x *= 0.92f;
	}
	//TODO: Test following line ??? 
	player_.player_velocity_.x += player_.player_speed_.x;

	delta += sf::Vector2f(player_.player_velocity_.x, player_.player_velocity_.y);
	
	sf::Vector2f temp_pos(player_.getPosition());
	//Position is a sum of speeds 
	player_.setPosition(temp_pos.x += delta.x, temp_pos.y += delta.y);
	if (player_.getPosition().x >= limit_x_high - (player_.player_size_.x / 2)) {
		player_.setPosition(limit_x_high - (player_.player_size_.x / 2), temp_pos.y);
	}
	if (player_.getPosition().x <= limit_x_low + (player_.player_size_.x / 2)) {
		player_.setPosition(limit_x_low + (player_.player_size_.x / 2), temp_pos.y);
	}
	player_.grounded_ = false;
	if (player_.getPosition().y >= limit_y_high - (player_.player_size_.y / 2)) {
		player_.setPosition(temp_pos.x, limit_y_high - (player_.player_size_.y / 2));
		player_.grounded_ = true;
	}
	if (player_.getPosition().y <= limit_y_low + (player_.player_size_.y / 2)) {
		player_.setPosition(temp_pos.x, limit_y_low + (player_.player_size_.y / 2));
		player_.player_velocity_.y = 0;
	}

	//TODO: Virer player_pos_ et utiliser play_.get/set position à la place, OU (plutôt ça) prendre la position avant mouvement, mettre dans une variable (ou dans player_pos_), effectuer les modifications sur la variable puis setPosition à la variable
	player_.setPosition(temp_pos);
	if (Level::GetTileAt(player_coords).deadly_) {
		std::cout << "u ded" << std::endl;
		player_.ResetPosition(Level::GetRespawnPoint());
	}


	//Drawing the tiles
	Level::DrawLevel(window_);

	// Visualize limits
	debug_limit_shape_vertical_.setPosition(limit_x_high, 0);
	window_.draw(debug_limit_shape_vertical_);
	debug_limit_shape_vertical_.setPosition(limit_x_low, 0);
	window_.draw(debug_limit_shape_vertical_);
	debug_limit_shape_horizontal_.setPosition(0, limit_y_high);
	window_.draw(debug_limit_shape_horizontal_);
	debug_limit_shape_horizontal_.setPosition(0, limit_y_low);
	window_.draw(debug_limit_shape_horizontal_);


	//player_.setPosition(player_.player_pos_.x, player_.player_pos_.y);
	view_.setCenter(player_.getPosition());

	window_.draw(player_);
	//player1_hitbox.setPosition(player_bounds.left, player_bounds.top);
	//window.DrawLevel(player1_hitbox);

	//window_.setView(view_);
	// Window Display
	window_.display();

}

