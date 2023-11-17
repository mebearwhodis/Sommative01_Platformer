#include "Editor.h"

#include <iostream>


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

	background_sprite_.setTexture(Texture::background_texture_);
	background_sprite_.setOrigin(background_sprite_.getGlobalBounds().width / 2, background_sprite_.getGlobalBounds().height / 2);

	//Cursor Tile
	hovered_tile_.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	hovered_tile_.setFillColor(sf::Color(100, 100, 100, 180));
	hovered_tile_.setOutlineColor(sf::Color::Magenta);
	hovered_tile_.setOutlineThickness(-1);
	hovered_tile_.setOrigin(0, 0);
}

void Editor::update()
{
	const int level_width = Level::GetLevelWidth();
	const int level_height = Level::GetLevelHeight();

	window_.clear(sf::Color::Black);
	sf::Event event;
	while (window_.pollEvent(event)) {
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window_.close();
		}
		//---------Key 0
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		{
			stamp_type_ = !stamp_type_;
		}
		//---------Key 1
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			if(stamp_type_)
			{
				selected_tile_ = { TileType::kGrass, true, false };
			}else
			{
				selected_interact_ = { InteractiveType::kCheckpoint, false, false };
			}
		}
		//---------Key 2
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			if (stamp_type_)
			{
				selected_tile_ = { TileType::kDirt, true, true };
			}
			else
			{
				selected_interact_ = { InteractiveType::kCoin, true, false };
			}
		}
		//---------Key 3
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			if (stamp_type_)
			{
				selected_tile_ = { TileType::kGrass, true, false };
			}
			else
			{
				selected_interact_ = { InteractiveType::kDiamond, true, false };
			}
		}
		//---------Key 4
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			if (stamp_type_)
			{
				selected_tile_ = { TileType::kGrass, true, false };
			}
			else
			{
				selected_interact_ = { InteractiveType::kFloatingSpikes, false, true };
			}
		}
		//---------Key 5
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			if (stamp_type_)
			{
				selected_tile_ = { TileType::kGrass, true, false };
			}
			else
			{
				selected_interact_ = { InteractiveType::kSpikes, false, true };
			}
		}
		//---------Key 6
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		{
			if (stamp_type_)
			{
				selected_tile_ = { TileType::kGrass, true, false };
			}
			else
			{
				selected_interact_ = { InteractiveType::kStar, false, false };
			}
		}

		//Resets the tiles
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			for (int i = 0; i < level_width * level_height; ++i)
			{
				Level::SetTileAt(Tile(TileType::kEmpty, false, false), i);
				Level::SetTileSprite(Texture::GetTileTextureFromType(TileType::kEmpty),i);

				Level::SetInteractAt(Interactive(InteractiveType::kEmpty, false, false), i);
				Level::SetInteractSprite(Texture::GetTileTextureFromType(TileType::kEmpty),i);
			}
		}
		// Saves the level
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
		{
			Level::SaveLevelToJson("levelOne.json");
		}

		// Loads the level
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9))
		{
			Level::LoadLevelFromJson("levelOne.json");
		}
	}

	//TODO: View that we can move with wasd (or mouse?) zoom, dezoom. Add more sprites, add coins and powerup and mobs (probably in another tilemap?)

	const sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_);
	const sf::Vector2i mouse_tile_coord(mouse_pos.x / TILE_SIZE, mouse_pos.y / TILE_SIZE);
	hovered_tile_.setPosition(static_cast<float>(mouse_tile_coord.x) * TILE_SIZE, static_cast<float>(mouse_tile_coord.y) * TILE_SIZE);




	
	//Editor interaction
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (mouse_tile_coord.x >= 0 && mouse_tile_coord.x < level_width && mouse_tile_coord.y >= 0 && mouse_tile_coord.y < level_height)
		{
			const int index = mouse_tile_coord.y * level_width + mouse_tile_coord.x;
			if (stamp_type_)
			{
				Level::SetTileAt(selected_tile_, index);
				Level::SetTileSprite(Texture::GetTileTextureFromType(selected_tile_.tile_type_), index);
			}else
			{
				Level::SetInteractAt(selected_interact_, index);
				Level::SetInteractSprite(Texture::GetInteractTextureFromType(selected_interact_.interactive_type_), index);
			}
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (mouse_tile_coord.x >= 0 && mouse_tile_coord.x < level_width && mouse_tile_coord.y >= 0 && mouse_tile_coord.y < level_height)
		{
			const int index = mouse_tile_coord.y * level_width + mouse_tile_coord.x;
			if(stamp_type_)
			{
				Level::SetTileAt(Tile{ TileType::kEmpty, false, false }, index);
			}else
			{
				Level::SetInteractAt(Interactive{ InteractiveType::kEmpty, false, false }, index);
			}
		}
	}



	Level::DrawLevel(window_);
	window_.draw(hovered_tile_);


	//window.setView(view);
	// Window Display
	window_.display();
}