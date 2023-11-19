#pragma once
#include <SFML/Graphics.hpp>


class HUD final : public sf::Drawable
{
    sf::Font font_;

    sf::Text timer_text_;
    sf::Text score_text_;
    sf::Text lives_text_;
    sf::Text stamp_type_text_;
    sf::Text selected_tile_text_;
    sf::Text you_win_;
    sf::Text you_lost_;
    

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:

    sf::RenderTarget* window_;
    sf::Clock timer_;
    float elapsed_time_seconds_;
    float GetElapsedTime() const { return elapsed_time_seconds_; }

    void init(const sf::RenderTarget& window);
    void update(const sf::View& view);
    void EndUpdate(const sf::View& view);
    void WinDraw(sf::RenderTarget& target) const;
    void LoseDraw(sf::RenderTarget& target) const;
};
