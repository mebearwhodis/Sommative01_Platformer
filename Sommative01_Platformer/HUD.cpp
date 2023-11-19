#include "HUD.h"
#include "Editor.h"
#include <sstream>

#include "Level.h"

void HUD::init(sf::RenderTarget& window)
{
	if (font_.loadFromFile("data/arial.ttf"))
	{
		timer_text_.setFont(font_);
		timer_text_.setString("");
		timer_text_.setCharacterSize(100);
		timer_text_.setFillColor(sf::Color::White);
		timer_text_.setOutlineThickness(2);
		timer_text_.setOutlineColor(sf::Color::Black);
		timer_text_.setStyle(sf::Text::Bold);
		timer_text_.setPosition(100.f, 50.f);

		score_text_.setFont(font_);
		score_text_.setString("");
		score_text_.setCharacterSize(100);
		score_text_.setFillColor(sf::Color::White);
		score_text_.setOutlineThickness(2);
		score_text_.setOutlineColor(sf::Color::Black);
		score_text_.setStyle(sf::Text::Bold);
		score_text_.setPosition(100.f, 150.f);

		lives_text_.setFont(font_);
		lives_text_.setString("");
		lives_text_.setCharacterSize(100);
		lives_text_.setFillColor(sf::Color::White);
		lives_text_.setOutlineThickness(2);
		lives_text_.setOutlineColor(sf::Color::Black);
		lives_text_.setStyle(sf::Text::Bold);
		lives_text_.setPosition(100.f, 250.f);
	}

}

void HUD::update(const sf::View& view)
{
	//Update timer
	timer_text_.setPosition(view.getCenter().x - view.getSize().x / 2 + 10, view.getCenter().y - view.getSize().y / 2 + 10);
	std::ostringstream time_string;
	time_string << "Time: " << GetElapsedTime();
	timer_text_.setString(time_string.str());

	//Update score
	score_text_.setPosition(view.getCenter().x - view.getSize().x / 2 + 10, view.getCenter().y - view.getSize().y / 2 + 110);
	std::ostringstream score_string;
	score_string << "Score: " << Level::GetScore();
	score_text_.setString(score_string.str());

	//Update lives
	lives_text_.setPosition(view.getCenter().x - view.getSize().x / 2 + 10, view.getCenter().y - view.getSize().y / 2 + 210);
	std::ostringstream lives_string;
	lives_string << "Lives: " << Level::GetLives();
	lives_text_.setString(lives_string.str());
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw HUD elements on the window
	target.draw(timer_text_);
	target.draw(score_text_);
	target.draw(lives_text_);
}


