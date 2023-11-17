
#include <SFML/Graphics.hpp>
#include "ModePicker.h"
#include "Texture.h"
#include "Tile.h"
#include "Level.h"
#include "Editor.h"
#include "Game.h"


int main()
{
	//Game:
	Game game;
	game.init();
	while (game.window_.isOpen())
	{
		game.update();
	}

	//Editor:
	//Editor editor;
	//editor.init();

	//while (editor.window_.isOpen())
	//{
	//	editor.update();
	//}

	//Both:
	//ModePicker mode_picker;
	//const GameMode answer = mode_picker.ModeChoice();


	//switch (answer)
	//{
	//case(GameMode::kGame):
	//{
	//Game game;
	//	game.init();
	//	while (game.window_.isOpen())
	//	{
	//		game.update();
	//	}
	//	break;
	//}
	//case GameMode::kEditor:
	//{
	//	Editor editor;
	//	editor.init();

	//	while (editor.window_.isOpen())
	//	{
	//		editor.update();
	//	}
	//	break;
	//}

	//case GameMode::kNone:
	//	break;
	//}

	//return 0;
};