#include "Editor.h"
#include "Game.h"
#include "ModePicker.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>

#include "Level.h"
#include "Texture.h"

int main()
{
	GameMode answer = ModePicker::ModeChoice();
	switch (answer)
	{
	case(GameMode::kGame):
	{
		Game game;
		game.init();

		while (game.window_.isOpen())
		{
			sf::Event event;
			while (game.window_.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					game.window_.close();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					//TODO: Function to reset player position
					game.player_.ResetPosition(Level::GetRespawnPoint());
				}
			}
			game.update();
		}
		break;
	}
	case GameMode::kEditor:
	{
		Editor editor;
		editor.init();

		while (editor.window_.isOpen())
		{
			sf::Event event;
			while (editor.window_.pollEvent(event)) {
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					editor.window_.close();
				}

				//Resets the tiles
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
				{
					int a = 0;
					for (Tile i : Level::tile_map_)
					{
						Level::SetTileAt({Tile(TileType::kEmpty, false, false)}, a);
						//Level::tile_map_[a].sprite_.setTexture(Texture::type_to_texture_.at(Level::tile_map_[a].tile_type_));
						a++;
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
			editor.update();
		}
		break;
	}

	case GameMode::kNone:
		break;
	}

	return 0;
};