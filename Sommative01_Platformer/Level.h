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
    std::vector<Tile> tile_map_;

public:

    //Constructor
    Level(sf::Vector2f starting_point, int level_width, int level_height, const sf::Texture& background_texture);

    //Getters & Setters
    sf::Vector2f GetRespawnPoint() const { return respawn_point_; }
    void SetRespawnPoint(const sf::Vector2f respawn_point) { respawn_point_ = respawn_point; }

    int GetLevelWidth() const { return level_width_; }
    int GetLevelHeight() const { return level_height_; }

	std::vector<Tile> GetTileMap() { return tile_map_; }

    Tile GetTileAt(sf::Vector2i tile_coord) const;
    Tile GetTileAt(const int index) { return tile_map_.at(index); }

    void SetTileAt(const Tile& t, const int index) { tile_map_.at(index) = t; }
    void SetTileTypeAt(const TileType t, const int index) { tile_map_.at(index).tile_type_ = t; }
    void SetTileSprite(const sf::Texture& t, const int index) { tile_map_.at(index).sprite_.setTexture(t); }


    sf::Sprite GetBackgroundSprite() const { return background_sprite_; }
    void SetBackgroundSprite(const sf::Texture& texture){background_sprite_.setTexture(texture);}
    void SetBackgroundOrigin(const sf::Vector2f origin) { background_sprite_.setOrigin(origin); }
    void SetBackgroundPosition(const sf::Vector2f position) { background_sprite_.setPosition(position); }

    //Utility
	static sf::Vector2i PosToCoords(sf::Vector2f world_pos);
    void DrawLevel(sf::RenderTarget& target);
    void SaveLevelToJson(const std::string& file_name);
    void LoadLevelFromJson(const std::string& file_path, Texture texture);
};

// Utiliser le std::_Erase_remove_if(VECTEUR, DEBUT, FIN)