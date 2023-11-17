#include "ModePicker.h"
#include <SFML/Graphics.hpp>

GameMode ModePicker::ModeChoice()
{
	{
		window_.create(sf::VideoMode(800, 600), "Game Modes Menu");
		sf::Font font;
		font.loadFromFile("data/arial.ttf");

		sf::Text title("Select Game Mode", font, 30);
		title.setPosition(280.f, 50.f);

		sf::Text game_mode("Play the Game", font, 20);
		game_mode.setPosition(350.f, 200.f);

		sf::Text editor_mode("Level Editor", font, 20);
		editor_mode.setPosition(350.f, 250.f);

		GameMode selected_mode = GameMode::kNone;

		while (window_.isOpen()) {
			sf::Event event;
			while (window_.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window_.close();
				}

				if (event.type == sf::Event::MouseButtonPressed) {
					const sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_);

					if (game_mode.getGlobalBounds().contains(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y))) {
						selected_mode = GameMode::kGame;
						return selected_mode;

					}
					else if (editor_mode.getGlobalBounds().contains(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y))) {
						selected_mode = GameMode::kEditor;
						return selected_mode;
					}
				}
			}

			window_.clear();
			window_.draw(title);
			window_.draw(game_mode);
			window_.draw(editor_mode);
			window_.display();
		}
		return GameMode::kNone;
	}
}
