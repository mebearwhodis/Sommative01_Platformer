#include "HUD.h"
#include "Editor.h"
#include <sstream>

#include "Level.h"

void HUD::init(const sf::RenderTarget& window)
{
	if (font_.loadFromFile("data/font/DynaPuff-Regular.ttf"))
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

		you_win_.setFont(font_);
		you_win_.setString("Congratulations!");
		you_win_.setCharacterSize(200);
		you_win_.setFillColor(sf::Color::White);
		you_win_.setOutlineThickness(2);
		you_win_.setOutlineColor(sf::Color::Magenta);
		you_win_.setStyle(sf::Text::Bold);
		you_win_.setPosition(125, window.getSize().y / 2 - 200);

		you_lost_.setFont(font_);
		you_lost_.setString("Sorry, you lost...");
		you_lost_.setCharacterSize(200);
		you_lost_.setFillColor(sf::Color::White);
		you_lost_.setOutlineThickness(2);
		you_lost_.setOutlineColor(sf::Color::Red);
		you_lost_.setStyle(sf::Text::Bold);
		you_lost_.setPosition(150, window.getSize().y / 2 - 200);
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

void HUD::EndUpdate(const sf::View& view)
{
	timer_text_.setPosition(530, view.getSize().y / 2 - 200);
	std::ostringstream time_string;
	time_string << "Final Time: " << GetElapsedTime();
	timer_text_.setString(time_string.str());

	score_text_.setPosition(730, view.getSize().y / 2);
	std::ostringstream score_string;
	score_string << "Final Score: " << Level::GetScore();
	score_text_.setString(score_string.str());
	//Update lives
	lives_text_.setPosition(530, view.getSize().y / 2 + 200);
	std::ostringstream lives_string;
	lives_string << "Remaining Lives: " << Level::GetLives();
	lives_text_.setString(lives_string.str());
}

void HUD::WinDraw(sf::RenderTarget& target) const
{
	target.draw(timer_text_);
	target.draw(score_text_);
	target.draw(lives_text_);
	target.draw(you_win_);
}

void HUD::LoseDraw(sf::RenderTarget& target) const
{
	target.draw(you_lost_);
	target.draw(score_text_);
}
