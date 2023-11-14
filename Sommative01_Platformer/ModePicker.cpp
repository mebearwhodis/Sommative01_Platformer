#include "ModePicker.h"
#include <SFML/Graphics.hpp>

GameMode ModePicker::ModeChoice()
{
	{
		sf::RenderWindow window(sf::VideoMode(800, 600), "Game Modes Menu");
		sf::Font font;
		font.loadFromFile("data/arial.ttf");

		sf::Text title("Select Game Mode", font, 30);
		title.setPosition(280.f, 50.f);

		sf::Text game_mode("Play the Game", font, 20);
		game_mode.setPosition(350.f, 200.f);

		sf::Text editor_mode("Level Editor", font, 20);
		editor_mode.setPosition(350.f, 250.f);

		GameMode selected_mode = GameMode::kNone;

		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}

				if (event.type == sf::Event::MouseButtonPressed) {
					sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

					if (game_mode.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
						selected_mode = GameMode::kGame;
						return selected_mode;
						window.close(); // Replace with logic to start Game

					}
					else if (editor_mode.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
						selected_mode = GameMode::kEditor;
						return selected_mode;
						window.close(); // Replace with logic to start Editor
					}
				}
			}

			window.clear();
			window.draw(title);
			window.draw(game_mode);
			window.draw(editor_mode);
			window.display();
		}
		return GameMode::kNone;
	}
}
