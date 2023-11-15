#pragma once
#include "Player.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>

class Level {

	//Things to add in case of multiple levels : 
	//std::string name_; Name to display in HUD
	//LevelType Normal, Water, Low Grav,...

    sf::Vector2f respawn_point_;
    int level_width_;
    int level_height_;
    sf::Sprite background_sprite_;
    Tile tile_map_[500];

public:

    //Constructor
    Level(sf::Vector2f starting_point, int level_width, int level_height);

    //Getters & Setters
    sf::Vector2f GetRespawnPoint() const { return respawn_point_; }
    void SetRespawnPoint(const sf::Vector2f respawn_point) { respawn_point_ = respawn_point; }

    int GetLevelWidth() const { return level_width_; }
    int GetLevelHeight() const { return level_height_; }

    Tile GetTileMap() { return *tile_map_; }

    Tile GetTileAt(const sf::Vector2i tile_coord) const;
    Tile GetTileAt(const int index) { return tile_map_[index]; }

    void SetTileAt(const Tile& t, const int index);
    void SetTileTypeAt(const TileType t, const int index);
    void SetTileSprite(const sf::Texture& t, const int index);

    sf::Sprite GetBackgroundSprite() const { return background_sprite_; }
    void SetBackgroundSprite(const sf::Texture& texture);

    //Utility
    sf::Vector2i PosToCoords(sf::Vector2f world_pos) const;
    void DrawLevel(sf::RenderTarget& target) const;
    void SaveLevelToJson(const std::string& file_name) const;
    void LoadLevelFromJson(const std::string& file_path);
};