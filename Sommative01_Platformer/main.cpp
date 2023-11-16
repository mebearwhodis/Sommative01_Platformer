#include "Editor.h"
#include "Game.h"
#include "ModePicker.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>

#include "Level.h"
#include "Texture.h"

int main()
{
	ModePicker mode_picker;
	GameMode answer = mode_picker.ModeChoice();
	Texture textures;
	textures.LoadTextures();
	Level level_one(sf::Vector2f(128 * 7 + 64, 128 * 2), 20, 6, textures.GetBackgroundTexture());

	switch (answer)
	{
	case(GameMode::kGame):
	{
		Game game;
		game.init(level_one, textures);

		while (game.window_.isOpen())
		{
			game.update(level_one, textures);
		}
		break;
	}
	case GameMode::kEditor:
	{
		Editor editor;
		editor.init();

		while (editor.window_.isOpen())
		{
			editor.update(level_one, textures);
		}
		break;
	}

	case GameMode::kNone:
		break;
	}

	return 0;
};