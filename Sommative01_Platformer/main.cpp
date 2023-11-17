
#include <SFML/Graphics.hpp>
#include "ModePicker.h"
#include "Texture.h"
#include "Tile.h"
#include "Level.h"
#include "Editor.h"
#include "Game.h"


int main()
{
	//ModePicker mode_picker;
	//GameMode answer = mode_picker.ModeChoice();
	Texture::LoadTextures();
	const Level level_one(sf::Vector2f(128 * 7 + 64, 128 * 2), 100, 5);

	//switch (answer)
	//{
	//case(GameMode::kGame):
	//{
	//	Game game;
	//	game.init(level_one, textures);

	//	while (game.window_.isOpen())
	//	{
	//		game.update(level_one, textures);
	//	}
	//	break;
	//}
	//case GameMode::kEditor:
	//{
		Editor editor;
		editor.init();

		while (editor.window_.isOpen())
		{
			editor.update(level_one);
		}
	//	break;
	//}

	//case GameMode::kNone:
	//	break;
	//}

	return 0;
};