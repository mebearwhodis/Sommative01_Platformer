#pragma once
#include "Player.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>

class Level
{
    //Things to add in case of multiple levels : 
    //std::string name_; Name to display in HUD
    //LevelType Normal, Water, Low Grav,...

    static sf::Vector2f respawn_point_;
    static int level_width_;
    static int level_height_;

public:
    static sf::Sprite background_sprite_;
    static Tile tile_map_[500];

    //Level Constructor
    Level(sf::Vector2f starting_point, int level_width, int level_height);

    //Getters & Setters
    static sf::Vector2f GetRespawnPoint() { return respawn_point_; }
    static void SetRespawnPoint(const sf::Vector2f respawn_point) { respawn_point_ = respawn_point; }

    static int GetLevelWidth() { return level_width_; }
    static int GetLevelHeight() { return level_height_; }

    static Tile GetTileMap() { return *tile_map_; }

    static Tile GetTileAt(const sf::Vector2i tile_coord)
    {
	    if (tile_coord.x >= 0 || tile_coord.x < level_width_ || tile_coord.y >= 0 || tile_coord.y < level_height_) { return tile_map_[tile_coord.y * level_width_ + tile_coord.x]; }
	    return {};
    }

    static Tile GetTileAt(const int index) { return tile_map_[index]; }
    static void SetTileAt(const Tile& t, const int index) { tile_map_[index] = t; }
    static void SetTileTypeAt(const TileType t, const int index) { tile_map_[index].tile_type_ = t; }
    static void SetTileSprite(const sf::Texture& t, const int index) { tile_map_[index].sprite_.setTexture(t); }

    static sf::Sprite GetBackgroundSprite() { return background_sprite_; }
    static  void SetBackgroundSprite(const sf::Texture& texture) { background_sprite_.setTexture(texture); }


    //Utility
    static sf::Vector2i PosToCoords(sf::Vector2f world_pos);

    static void DrawLevel(sf::RenderTarget& target);

    static void SaveLevelToJson(const std::string& file_name);
    static void LoadLevelFromJson(const std::string& file_path);
};

