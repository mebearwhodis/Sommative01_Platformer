
#include <SFML/Graphics.hpp>
#include "ModePicker.h"
#include "Texture.h"
#include "Tile.h"
#include "Level.h"
#include "Editor.h"
#include "Game.h"


int main()
{
	ModePicker mode_picker;
	const GameMode answer = mode_picker.ModeChoice();
	Texture temp_texture;
	temp_texture.LoadTextures();

	const Texture texture = temp_texture;

	switch (answer)
	{
	case(GameMode::kGame):
	{
		Game game;
		game.init();

		while (game.window_.isOpen())
		{
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
			editor.update(texture);
		}
		break;
	}

	case GameMode::kNone:
		break;
	}

	return 0;
};