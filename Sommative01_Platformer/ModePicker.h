#pragma once
#include <SFML/Graphics.hpp>

enum class GameMode {
	kGame,
	kEditor,
	kNone
};

class ModePicker
{
	sf::RenderWindow window_;

public:
	GameMode ModeChoice();
};



