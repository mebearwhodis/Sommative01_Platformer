#include "Editor.h"

#include <iostream>


void Editor::init()
{


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
}

void Editor::update(const Level& level)
{
	window_.clear(sf::Color::Black);
	Texture::LoadTextures();
	sf::Event event;
	while (window_.pollEvent(event)) {
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window_.close();
		}
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Num1)))
		{
			selected_tile_type_ = TileType::kGrass;
		}
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Num2)))
		{
			selected_tile_type_ = TileType::kDirt;
		}
		//Resets the tiles
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			for (int i = 0; i < level.GetLevelWidth() * level.GetLevelHeight(); ++i)
			{
				Level::SetTileAt(Tile(TileType::kEmpty, false, false), i);
				//level.SetTileSprite(texture.GetTextureMap().at(level.GetTileAt(i).tile_type_), i);
			}
		}
		// Saves the level
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
		{
			level.SaveLevelToJson("levelOne.json");
		}

		// Loads the level
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9))
		{
			Level::LoadLevelFromJson("levelOne.json");
		}
	}

	//TODO: View that we can move with wasd (or mouse?) zoom, dezoom. Add more sprites, add coins and powerup and mobs (probably in another tilemap?)
	const int level_width = level.GetLevelWidth();
	const int level_height = level.GetLevelHeight();

	const sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_);
	const sf::Vector2i mouse_tile_coord(mouse_pos.x / TILE_SIZE, mouse_pos.y / TILE_SIZE);
	hovered_tile_.setPosition(static_cast<float>(mouse_tile_coord.x) * TILE_SIZE, static_cast<float>(mouse_tile_coord.y) * TILE_SIZE);




	
	//Editor interaction
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (mouse_tile_coord.x >= 0 && mouse_tile_coord.x < level_width && mouse_tile_coord.y >= 0 && mouse_tile_coord.y < level_height)
		{
			std::cout << "Type: " << static_cast<int>(level.GetTileTypeAt(mouse_tile_coord)) << std::endl;
			const int index = mouse_tile_coord.y * level_width + mouse_tile_coord.x;
			Level::SetTileTypeAt(selected_tile_type_, index);
			Level::SetTileSprite(Texture::GetTextureFromType(selected_tile_type_),index);

			std::cout << "Type: " << static_cast<int>(level.GetTileTypeAt(mouse_tile_coord)) << std::endl << "----------------" << std::endl;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (mouse_tile_coord.x >= 0 && mouse_tile_coord.x < level_width && mouse_tile_coord.y >= 0 && mouse_tile_coord.y < level_height)
		{
			const int index = mouse_tile_coord.y * level_width + mouse_tile_coord.x;
			Level::SetTileAt(Tile{ TileType::kEmpty, false, false }, index);
		}
	}



	level.DrawLevel(window_);
	window_.draw(hovered_tile_);


	//window.setView(view);
	// Window Display
	window_.display();
}