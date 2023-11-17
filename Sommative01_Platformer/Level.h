#pragma once
#include "Player.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>

#include "Texture.h"

class Level {

	//Things to add in case of multiple levels : 
	//std::string name_; Name to display in HUD
	//LevelType Normal, Water, Low Grav,...

    sf::Vector2f respawn_point_;
    int level_width_;
    int level_height_;
    sf::Sprite background_sprite_;

    //I'd rather not use a static tile_map, but it's the only way I got the game to work and I only have one level for now so it's a temporary fix
    static Tile tile_map_[500];

public:

    //Constructor
    Level(sf::Vector2f starting_point, int level_width, int level_height);

    //Getters & Setters
    sf::Vector2f GetRespawnPoint() const { return respawn_point_; }
    void SetRespawnPoint(const sf::Vector2f respawn_point) { respawn_point_ = respawn_point; }

    int GetLevelWidth() const { return level_width_; }
    int GetLevelHeight() const { return level_height_; }

	static Tile GetTileMap() { return *tile_map_; }

    Tile GetTileAt(sf::Vector2i tile_coord) const;
	static Tile GetTileAt(const int index) { return tile_map_[index]; }
    TileType GetTileTypeAt(sf::Vector2i tile_coord) const;
	static TileType GetTileTypeAt(const int index) { return tile_map_[index].tile_type_; }

	static void SetTileAt(const Tile& t, const int index)
    {
	    tile_map_[index] = t;
        tile_map_[index].sprite_.setTexture(Texture::GetTextureFromType(t.tile_type_));
    }

	static void SetTileTypeAt(const TileType t, const int index) { tile_map_[index].tile_type_ = t; }
	static void SetTileSprite(const sf::Texture& t, const int index) { tile_map_[index].sprite_.setTexture(t); }


    sf::Sprite GetBackgroundSprite() const { return background_sprite_; }
    void SetBackgroundSprite(const sf::Texture& texture){background_sprite_.setTexture(texture);}
    void SetBackgroundOrigin(const sf::Vector2f origin) { background_sprite_.setOrigin(origin); }
    void SetBackgroundPosition(const sf::Vector2f position) { background_sprite_.setPosition(position); }

    //Utility
	static sf::Vector2i PosToCoords(sf::Vector2f world_pos);
    void DrawLevel(sf::RenderTarget& target) const;
    void SaveLevelToJson(const std::string& file_name) const;
	static void LoadLevelFromJson(const std::string& file_path);
};

// Utiliser le std::_Erase_remove_if(VECTEUR, DEBUT, FIN)