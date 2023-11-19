#include "Game.h"
#include "HUD.h"
#include "Level.h"
#include "Texture.h"


void Game::init()
{
	Texture::LoadTextures();
	Level::LoadLevelFromJson("levelOne.json");

	//Basic Setup of the window
	window_.create(sf::VideoMode(800, 800), "The Game");
	window_.setFramerateLimit(30);
	window_.setVerticalSyncEnabled(true);
	window_.setMouseCursorVisible(false);

	//Set up the View
	view_.setSize(2000, 2000);
	view_.setCenter(1000, 1000);

	//Create collision lines
	debug_limit_shape_vertical_.setSize(sf::Vector2f(2, 100000));
	debug_limit_shape_vertical_.setOrigin(1, 0);
	debug_limit_shape_vertical_.setFillColor(sf::Color(255, 0, 255));
	debug_limit_shape_horizontal_.setSize(sf::Vector2f(100000, 2));
	debug_limit_shape_horizontal_.setOrigin(0, 1);
	debug_limit_shape_horizontal_.setFillColor(sf::Color(255, 0, 255));

	player_.ResetPosition(Level::GetRespawnPoint());

	background_sprite_.setTexture(Texture::background_texture_);
	background_sprite_.setOrigin(background_sprite_.getGlobalBounds().width / 2, background_sprite_.getGlobalBounds().height / 2);
	background_sprite_.scale(2.f, 2.f);

	hud_.init(window_);
	hud_.timer_.restart();
}

void Game::update()
{

	sf::Event event;

	while (window_.isOpen() && !is_game_over_)
	{
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window_.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				player_.ResetPosition(Level::GetRespawnPoint());
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

		SetBackgroundPosition(sf::Vector2f(view_.getCenter()));

		//Movement---------------------------------------------------------------------------------------------------------------------------------------------------

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
			player_.SetSprite(player_.left_);
			delta += sf::Vector2f(-1 * (player_.GetPlayerBaseSpeed().x + player_.GetPlayerSpeed().x) * speed_factor, 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player_.SetSprite(player_.right_);
			delta += sf::Vector2f((player_.GetPlayerBaseSpeed().x + player_.GetPlayerSpeed().x) * speed_factor, 0);
		}


		//TODO: Find a use for W & S, maybe some kind of powerup/groundpound
		//Capping falling speed
		if (player_.GetPlayerSpeed().y > 5)
		{
			player_.SetPlayerSpeed(sf::Vector2f(player_.GetPlayerSpeed().x, 5));
		}

		//Player_velocity is a summ of forces
		//Jump higher if you press longer
		const bool jump_key_is_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		if (jump_key_is_down && player_.GetGroundedValue())
		{
			player_.SetJumpForce(sf::Vector2f(0.0f, -35.0f));
		}

		player_.SetPlayerVelocity(sf::Vector2f(player_.GetPlayerVelocity().x, player_.GetPlayerVelocity().y + (jump_key_is_down ? 1.2f : 1.9f)));

		if (!player_.GetGroundedValue())
		{
			player_.SetPlayerVelocity(player_.GetPlayerVelocity() + gravity_force_);
		}
		//Cancel vertical velocity if grounded
		else
		{
			player_.SetPlayerVelocity(sf::Vector2f(player_.GetPlayerVelocity().x, 0));
		}

		player_.SetPlayerVelocity(player_.GetPlayerVelocity() + player_.GetJumpForce());


		//Horizontal deceleration and acceleration
		player_.SetPlayerSpeed(player_.GetPlayerSpeed() + player_.GetPlayerVelocity());
		if (!player_.GetGroundedValue())
		{
			player_.SetPlayerSpeed(sf::Vector2f(player_.GetPlayerSpeed().x * 0.9f, player_.GetPlayerSpeed().y));
		}
		else
		{
			if (std::abs(player_.GetPlayerSpeed().x) < 0.1)
			{
				player_.SetPlayerSpeed(sf::Vector2f(0, player_.GetPlayerSpeed().y));
			}
			player_.SetPlayerSpeed(sf::Vector2f(player_.GetPlayerSpeed().x * 0.92f, player_.GetPlayerSpeed().y));
		}


		delta += sf::Vector2f(player_.GetPlayerVelocity().x, player_.GetPlayerVelocity().y);

		//Position is a sum of speeds
		player_.setPosition(player_.getPosition().x + delta.x, player_.getPosition().y + delta.y);


		//Collision Handler----------------------------------------------------------------------------------------------------------------
		const sf::Vector2i player_coords = Level::PosToCoords(player_.getPosition());

		constexpr int margin = 1;

		if (Level::GetTileAt(player_coords + sf::Vector2i(1, 0)).solid_ || (player_coords + sf::Vector2i(1, 0)).x >=
			Level::GetLevelWidth()) {
			limit_x_high = static_cast<float>(player_coords.x + 1) * TILE_SIZE - margin;
		}
		if (Level::GetTileAt(player_coords + sf::Vector2i(-1, 0)).solid_ || (player_coords + sf::Vector2i(-1, 0)).x < 0) {
			limit_x_low = static_cast<float>(player_coords.x) * TILE_SIZE + margin;
		}
		if (Level::GetTileAt(player_coords + sf::Vector2i(0, 1)).solid_ || (player_coords + sf::Vector2i(0, 1)).y >=
			Level::GetLevelHeight()) {
			limit_y_high = static_cast<float>(player_coords.y + 1) * TILE_SIZE - margin;
		}
		if (Level::GetTileAt(player_coords + sf::Vector2i(0, -1)).solid_ || (player_coords + sf::Vector2i(0, -1)).y < 0) {
			limit_y_low = static_cast<float>(player_coords.y) * TILE_SIZE + margin;
		}

		if (player_.getPosition().x >= limit_x_high - (player_.GetPlayerSize().x / 2)) {
			player_.setPosition(limit_x_high - (player_.GetPlayerSize().x / 2), player_.getPosition().y);
		}
		if (player_.getPosition().x <= limit_x_low + (player_.GetPlayerSize().x / 2)) {
			player_.setPosition(limit_x_low + (player_.GetPlayerSize().x / 2), player_.getPosition().y);
		}
		player_.SetGroundedValue(false);
		if (player_.getPosition().y >= limit_y_high - (player_.GetPlayerSize().y / 2)) {
			player_.setPosition(player_.getPosition().x, limit_y_high - (player_.GetPlayerSize().y / 2));
			player_.SetGroundedValue(true);
		}
		if (player_.getPosition().y <= limit_y_low + (player_.GetPlayerSize().y / 2)) {
			player_.setPosition(player_.getPosition().x, limit_y_low + (player_.GetPlayerSize().y / 2));
			player_.SetPlayerVelocity(sf::Vector2f(player_.GetPlayerVelocity().x, 0));
		}


		//Interactables--------------------------------------------------------------------------------------------------------------------------------------
		if (Level::GetInteractAt(player_coords).deadly_) {
			player_.ResetPosition(Level::GetRespawnPoint());
			Level::LoseLife();
			if (Level::GetLives() <= 0)
			{
				is_game_over_ = true;
				is_game_won_ = false;
			}
		}
		if (Level::GetInteractAt(player_coords).temporary_ && !Level::GetInteractAt(player_coords).taken_) {
			Level::TakeItemAtCoords(player_coords);
		}
		if (Level::GetInteractAt(player_coords).interactive_type_ == InteractiveType::kCheckpoint) {
			// Update the current checkpoint to CheckpointUp and set it as the new respawn point
			Level::SetInteractAt(Interactive{ InteractiveType::kCheckpointUp, false, false, false }, player_coords.y * Level::GetLevelWidth() + player_coords.x);
			Level::SetInteractSprite(Texture::GetInteractTextureFromType(InteractiveType::kCheckpointUp), player_coords.y * Level::GetLevelWidth() + player_coords.x);
			Level::SetRespawnPoint(sf::Vector2f(player_coords * TILE_SIZE));

			for (int y = 0; y < Level::GetLevelHeight(); y++)
			{
				for (int x = 0; x < Level::GetLevelWidth(); x++)
				{
					sf::Vector2i coords(x, y);

					if (Level::GetInteractAt(coords).interactive_type_ == InteractiveType::kCheckpointUp && coords != player_coords) {
						// Change other CheckpointUp to Checkpoint
						Level::SetInteractAt(Interactive{ InteractiveType::kCheckpoint, false, false, false }, coords.y * Level::GetLevelWidth() + coords.x);
						//TODO: Getting white squares here
						Level::SetInteractSprite(Texture::GetInteractTextureFromType(InteractiveType::kCheckpoint), coords.y * Level::GetLevelWidth() + coords.x);
					}
				}
			}
		}
		if (Level::GetInteractAt(player_coords).interactive_type_ == InteractiveType::kStar)
		{
			is_game_over_ = true;
			is_game_won_ = true;
		}


		//Debugging-------------------------------------------------------------------------------------------------------------------------------------------------------
		//Visualize limits
		//debug_limit_shape_vertical_.setPosition(limit_x_high, 0);
		//window_.draw(debug_limit_shape_vertical_);
		//debug_limit_shape_vertical_.setPosition(limit_x_low, 0);
		//window_.draw(debug_limit_shape_vertical_);
		//debug_limit_shape_horizontal_.setPosition(0, limit_y_high);
		//window_.draw(debug_limit_shape_horizontal_);
		//debug_limit_shape_horizontal_.setPosition(0, limit_y_low);
		//window_.draw(debug_limit_shape_horizontal_);
		//system("cls");
		//std::cout << std::to_string(player_coords.x) << "-" << std::to_string(player_coords.y) << std::endl;
		//std::cout << std::to_string(view_.getCenter().x) << "-" << std::to_string(view_.getCenter().y) << std::endl;
		//std::cout << Level::GetLives() << std::endl;


		//View-------------------------------------------------------------------------------------------------------------------------------------------------------
		view_.setCenter(player_.getPosition().x, Level::GetLevelHeight() * static_cast<float>(TILE_SIZE / 2));
		//Stop the view at the edges of the level
		//Left ---------
		if (view_.getCenter().x < view_.getSize().x / 2)
		{
			view_.setCenter(view_.getSize().x / 2, view_.getCenter().y);
		}
		//Right ---------
		if (view_.getCenter().x + view_.getSize().x / 2 > TILE_SIZE * Level::GetLevelWidth())
		{
			view_.setCenter(TILE_SIZE * Level::GetLevelWidth() - view_.getSize().x / 2, view_.getCenter().y);
		}

		//The following two would be used in a more vertical level
		////Up ---------
		//if (view_.getCenter().y - view_.getSize().y / 2 < 0)
		//{
		//	view_.setCenter(player_.getPosition().x, view_.getSize().y / 2 + TILE_SIZE/2);
		//}
		////Down ---------
		//if (view_.getCenter().y + view_.getSize().y / 2 > TILE_SIZE * Level::GetLevelHeight())
		//{
		//	view_.setCenter(player_.getPosition().x, TILE_SIZE * Level::GetLevelHeight() - view_.getSize().y / 2);
		//}

		const sf::Time elapsed_time = hud_.timer_.getElapsedTime();
		hud_.elapsed_time_seconds_ = elapsed_time.asSeconds();
		hud_.update(view_);

		//Drawing the Level
		window_.draw(background_sprite_);
		Level::DrawLevel(window_);
		window_.draw(player_);
		window_.setView(view_);
		window_.draw(hud_);

		// Window Display
		window_.display();

	}
	while (window_.isOpen() && is_game_over_)
	{
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window_.close();
			}
		}
		if (is_game_over_ && is_game_won_)
		{
			window_.draw(background_sprite_);
			hud_.EndUpdate(view_);
			hud_.WinDraw(window_);
		}
		else if (is_game_over_ && !is_game_won_)
		{
			sf::RectangleShape darker;
			darker.setOrigin(view_.getCenter());
			darker.setSize(sf::Vector2f(view_.getSize().y + 500, view_.getSize().x + 500));
			darker.setPosition(view_.getCenter());
			darker.setFillColor(sf::Color(0, 0, 0, 200));
			window_.draw(background_sprite_);
			window_.draw(darker);
			hud_.EndUpdate(view_);
			hud_.LoseDraw(window_);
		}
		window_.display();
	}
}



