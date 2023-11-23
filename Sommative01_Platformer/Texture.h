#pragma once
#include "Tile.h"
#include <SFML/Graphics.hpp>

#include "Interactive.h"

class Texture
{
public:
    static sf::Texture empty_;
    static sf::Texture dirt_;
    static sf::Texture grass_;

    static sf::Texture checkpoint_down_;
    static sf::Texture checkpoint_up1_;
    static sf::Texture checkpoint_up2_;
    static std::vector <sf::Texture> checkpoint_;
    static sf::Texture coin_;
    static sf::Texture diamond_;
    static sf::Texture floating_spike1_;
    static sf::Texture floating_spike2_;
    static std::vector <sf::Texture> floating_spike_;
    static sf::Texture spike1_;
    static sf::Texture spike2_;
    static std::vector <sf::Texture> grounded_spike_;
    static sf::Texture star_;

    static sf::Texture background_texture_;

    static std::map<TileType, sf::Texture> tile_type_to_texture_;
    static std::map<InteractiveType, sf::Texture> interact_type_to_texture_;

    static void LoadTextures();

    //sf::Texture GetEmptyTexture() { return empty_; }
    //sf::Texture GetDirtTexture() { return dirt_; }
    //sf::Texture GetGrassTexture() { return grass_; }
    //sf::Texture GetStartTexture() { return start_; }
    //sf::Texture GetEndTexture() { return end_; }
    static sf::Texture GetBackgroundTexture() { return background_texture_; }

    static sf::Texture GetTileTextureFromType(const TileType t) { return tile_type_to_texture_.at(t); }
    static sf::Texture GetInteractTextureFromType(const InteractiveType t) { return interact_type_to_texture_.at(t); }
};
