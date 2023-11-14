#include "Editor.h"

#include "Level.h"
#include "Texture.h"


void Editor::init()
{
	Texture::LoadTextures();

	//View
	/*sf::View view;
	view.setSize(1200, 900);*/


	// Basic Setup of the window
	// Vertical sync, framerate
	window_.create(sf::VideoMode(1200, 900), "Level Editor");
	window_.setVerticalSyncEnabled(false);
	window_.setFramerateLimit(30);

	window_.setMouseCursorVisible(false);
	window_.setKeyRepeatEnabled(true);

	//Cursor Tile
	hovered_tile_.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	hovered_tile_.setFillColor(sf::Color(100, 100, 100, 180));
	hovered_tile_.setOutlineColor(sf::Color::Magenta);
	hovered_tile_.setOutlineThickness(-1);
	hovered_tile_.setOrigin(0, 0);


	Level level_one(sf::Vector2f(50, 50), 50, 10);
}

void Editor::update()
{
	//TODO: View that we can move with wasd (or mouse?) zoom, dezoom. Add more sprites, add coins and powerup and mobs (probably in another tilemap?)
	const int level_width = Level::GetLevelWidth();
	const int level_height = Level::GetLevelHeight();

	const sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_);
	const sf::Vector2i mouse_tile_coord(mouse_pos.x / TILE_SIZE, mouse_pos.y / TILE_SIZE);
	hovered_tile_.setPosition(mouse_tile_coord.x * TILE_SIZE, mouse_tile_coord.y * TILE_SIZE);

	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Num1)))
	{
		selected_tile_type_ = TileType::kGrass;
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Num2)))
	{
		selected_tile_type_ = TileType::kDirt;
	}

	
	//Editor interaction
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (mouse_tile_coord.x < 0 || mouse_tile_coord.x >= level_width || mouse_tile_coord.y < 0 || mouse_tile_coord.y >= level_height)
		{
		}
		else
		{
			Level::SetTileTypeAt(selected_tile_type_, mouse_tile_coord.y * level_width + mouse_tile_coord.x);
			Level::SetTileSprite(Texture::type_to_texture_.at(Level::GetTileAt(mouse_tile_coord.y * level_width + mouse_tile_coord.x).tile_type_), mouse_tile_coord.y * level_width + mouse_tile_coord.x);

		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (mouse_tile_coord.x < 0 || mouse_tile_coord.x >= level_width || mouse_tile_coord.y < 0 || mouse_tile_coord.y >= level_height)
		{
		}
		else
		{
			Level::SetTileTypeAt(TileType::kEmpty, mouse_tile_coord.y * level_width + mouse_tile_coord.x);
			Level::SetTileSprite(Texture::type_to_texture_.at(Level::GetTileAt(mouse_tile_coord.y * level_width + mouse_tile_coord.x).tile_type_), mouse_tile_coord.y * level_width + mouse_tile_coord.x);
		}
	}




	// Visualize limits

	window_.clear(sf::Color::Black);
	Level::DrawLevel(window_);
	window_.draw(hovered_tile_);


	//window.setView(view);
	// Window Display
	window_.display();
}