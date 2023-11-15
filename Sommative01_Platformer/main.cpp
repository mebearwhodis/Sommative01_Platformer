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
			editor.update();
		}
		break;
	}

	case GameMode::kNone:
		break;
	}

	return 0;
};