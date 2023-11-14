#pragma once

enum class GameMode {
	kGame,
	kEditor,
	kNone
};

class ModePicker
{
public:
	static GameMode ModeChoice();
};



