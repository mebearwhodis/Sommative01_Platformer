#pragma once
#include <SFML/Graphics.hpp>

enum class GameMode {
	kGame,
	kEditor,
	kNone
};

class ModePicker
{
public:
	sf::RenderWindow window_;
	GameMode ModeChoice();
};



