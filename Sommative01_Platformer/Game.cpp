#include "Game.h"

#include <iostream>

#include "Level.h"
#include "Texture.h"




void Game::init(const Level& level, const Texture& texture)
{
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

	player_.ResetPosition(level.GetRespawnPoint());
}

void Game::update(Level level, const Texture& texture)
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
			player_.ResetPosition(level.GetRespawnPoint());
		}
	}
	window_.clear();
	float limit_x_low = -1000000000.f;
	float limit_x_high = 1000000000.f;
	float limit_y_low = -1000000000.f;
	float limit_y_high = 1000000000.f;

	//Reset the forces
	player_.SetJumpForce(sf::Vector2f(0.0f, 0.0f));
	player_.SetMoveForce(sf::Vector2f(0.0f, 0.0f));

	level.SetBackgroundPosition(sf::Vector2f(player_.getPosition().x, player_.getPosition().y));

	// Collision debug lines
	const sf::Vector2i player_coords = level.PosToCoords(player_.getPosition());
	constexpr int margin = 1;

	if (level.GetTileAt(player_coords + sf::Vector2i(1, 0)).solid_ || (player_coords + sf::Vector2i(1, 0)).x >= level.GetLevelWidth()) {
		limit_x_high = (player_coords.x + 1) * TILE_SIZE - margin;
	}
	if (level.GetTileAt(player_coords + sf::Vector2i(-1, 0)).solid_ || (player_coords + sf::Vector2i(-1, 0)).x < 0) {
		limit_x_low = (player_coords.x) * TILE_SIZE + margin;
	}
	if (level.GetTileAt(player_coords + sf::Vector2i(0, 1)).solid_ || (player_coords + sf::Vector2i(0, 1)).y >= level.GetLevelHeight()) {
		limit_y_high = (player_coords.y + 1) * TILE_SIZE - margin;
	}
	if (level.GetTileAt(player_coords + sf::Vector2i(0, -1)).solid_ || (player_coords + sf::Vector2i(0, -1)).y < 0) {
		limit_y_low = (player_coords.y) * TILE_SIZE + margin;
	}



	//Movement - what will modify the speed vector

	//Sprint & Air Control
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		player_.SetSprintingState(true);
	}
	else
	{
		player_.SetSprintingState(false);
	}


	float speed_factor = player_.GetGroundedValue() ? 1.0f : 0.70f;
	if (player_.GetSprintingState())
	{
		speed_factor *= player_.GetSprintModifier();
	}

	//Left & Right
	sf::Vector2f delta(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player_.SetSprite(player_.GetTextureLeft());
		delta += sf::Vector2f(-1 * (player_.GetPlayerSpeed().x) * speed_factor, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player_.SetSprite(player_.GetTextureRight());
		delta += sf::Vector2f((player_.GetPlayerSpeed().x) * speed_factor, 0);
	}

	//Capping falling speed
	if (player_.GetPlayerSpeed().y > 3)
	{
		player_.SetPlayerSpeed(sf::Vector2f(player_.GetPlayerSpeed().x, 3));
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
	if (jump_key_is_down && player_.GetGroundedValue())
	{
		player_.SetJumpForce(sf::Vector2f(0.0f, -35.0f));
	}

	player_.SetPlayerVelocity(sf::Vector2f(player_.GetPlayerVelocity().x, player_.GetPlayerVelocity().y + (jump_key_is_down ? 0.0f : 1.5f)));

	if (!player_.GetGroundedValue())
	{
		player_.SetPlayerVelocity(player_.GetPlayerVelocity() + gravity_force_);
	}
	// Cancel vertical velocity if grounded
	else
	{
		player_.SetPlayerVelocity(sf::Vector2f(player_.GetPlayerVelocity().x, 0));
	}

	player_.SetPlayerVelocity(player_.GetPlayerVelocity() + player_.GetJumpForce());
	player_.SetPlayerVelocity(player_.GetPlayerVelocity() + player_.GetMoveForce());


	//Horizontal deceleration and acceleration
	player_.SetPlayerSpeed(player_.GetPlayerSpeed() + player_.GetPlayerVelocity());
	if (!player_.GetGroundedValue())
	{
		player_.SetPlayerSpeed(sf::Vector2f(player_.GetPlayerSpeed().x * 0.95f, player_.GetPlayerSpeed().y));
	}
	else
	{
		if (std::abs(player_.GetPlayerSpeed().x) < 0.3)
		{
			player_.SetPlayerSpeed(sf::Vector2f(0, player_.GetPlayerSpeed().y));
		}
		player_.SetPlayerSpeed(sf::Vector2f(player_.GetPlayerSpeed().x * 0.92f, player_.GetPlayerSpeed().y));
	}
	//TODO: Test following line ??? 
	player_.SetPlayerVelocity(sf::Vector2f(player_.GetPlayerVelocity().x + player_.GetPlayerSpeed().x, player_.GetPlayerVelocity().y));

	delta += sf::Vector2f(player_.GetPlayerVelocity().x, player_.GetPlayerVelocity().y);

	sf::Vector2f temp_pos(player_.getPosition());
	//Position is a sum of speeds 
	player_.setPosition(temp_pos.x += delta.x, temp_pos.y += delta.y);
	if (player_.getPosition().x >= limit_x_high - (player_.GetPlayerSize().x / 2)) {
		player_.setPosition(limit_x_high - (player_.GetPlayerSize().x / 2), temp_pos.y);
	}
	if (player_.getPosition().x <= limit_x_low + (player_.GetPlayerSize().x / 2)) {
		player_.setPosition(limit_x_low + (player_.GetPlayerSize().x / 2), temp_pos.y);
	}
	player_.SetGroundedValue(false);
	if (player_.getPosition().y >= limit_y_high - (player_.GetPlayerSize().y / 2)) {
		player_.setPosition(temp_pos.x, limit_y_high - (player_.GetPlayerSize().y / 2));
		player_.SetGroundedValue(true);
	}
	if (player_.getPosition().y <= limit_y_low + (player_.GetPlayerSize().y / 2)) {
		player_.setPosition(temp_pos.x, limit_y_low + (player_.GetPlayerSize().y / 2));
		player_.SetPlayerVelocity(sf::Vector2f(player_.GetPlayerVelocity().x, 0));
	}

	//TODO: Virer player_pos_, speed et velocity, assigner à des variables au début, modifier les variables pui Set dans la classe
	player_.setPosition(temp_pos);
	if (level.GetTileAt(player_coords).deadly_) {
		std::cout << "u ded" << std::endl;
		player_.ResetPosition(level.GetRespawnPoint());
	}


	//Drawing the tiles
	level.DrawLevel(window_);

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

