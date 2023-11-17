#pragma once
#include "Player.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>

#include "Texture.h"

class Level {

	//Things to add in case of multiple levels : 
	//std::string name_; Name to display in HUD
	//LevelType Normal, Water, Low Grav,...

    static sf::Vector2f respawn_point_;
    static int level_width_;
    static int level_height_;

    //I'd rather not use a static tile_map, but it's the only way I got the game to work and I only have one level for now so it's a temporary workaround
    static Tile tile_map_[1000];
    static Interactive interact_map_[1000];

public:

    //Getters & Setters
	static sf::Vector2f GetRespawnPoint() { return respawn_point_; }
	static void SetRespawnPoint(const sf::Vector2f respawn_point) { respawn_point_ = respawn_point; }

    static int GetLevelWidth() { return level_width_; }
    static int GetLevelHeight() { return level_height_; }

	static Tile GetTileMap() { return *tile_map_; }

	static Tile GetTileAt(sf::Vector2i tile_coord);
	static Tile GetTileAt(const int index) { return tile_map_[index]; }
	static TileType GetTileTypeAt(sf::Vector2i tile_coord);
	static TileType GetTileTypeAt(const int index) { return tile_map_[index].tile_type_; }

	static void SetTileAt(const Tile& t, const int index) { tile_map_[index] = t; }
	static void SetTileTypeAt(const TileType t, const int index) { tile_map_[index].tile_type_ = t; }
	static void SetTileSprite(const sf::Texture& t, const int index) { tile_map_[index].sprite_.setTexture(t); }

	static void SetInteractAt(const Interactive& t, const int index) { interact_map_[index] = t; }
	static void SetInteractSprite(const sf::Texture& t, const int index) { interact_map_[index].sprite_.setTexture(t); }


    //Utility
	static sf::Vector2i PosToCoords(sf::Vector2f world_pos);
	static void DrawLevel(sf::RenderTarget& target);
    static void SaveLevelToJson(const std::string& file_name);
	static void LoadLevelFromJson(const std::string& file_name);
};

// Utiliser le std::_Erase_remove_if(VECTEUR, DEBUT, FIN)