
#include <SFML/Graphics.hpp>
#include "ModePicker.h"
#include "Editor.h"
#include "Game.h"

//TODO: Add little Editor hub, add animations, maybe even sounds

int main()
{
	ModePicker mode_picker;
	const GameMode answer = mode_picker.ModeChoice();

	switch (answer)
	{
	case(GameMode::kGame):
	{
		Game game;
		game.init();
		game.update();
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