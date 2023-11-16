#include "Level.h"
#include "Texture.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

Level::Level(const sf::Vector2f starting_point, const int level_width, const int level_height, const sf::Texture& background_texture)
{
	respawn_point_ = starting_point;
	level_width_ = level_width;
	level_height_ = level_height;
	background_sprite_.setTexture(background_texture);
	background_sprite_.setOrigin(background_sprite_.getGlobalBounds().width / 2, background_sprite_.getGlobalBounds().height / 2);
	tile_map_.resize(level_width * level_height);

}

Tile Level::GetTileAt(const sf::Vector2i tile_coord) const
{
	if (tile_coord.x < 0 || tile_coord.y < 0 || tile_coord.x >= GetLevelWidth() || tile_coord.y >= GetLevelHeight())
	{
		return { Tile{TileType::kEmptySolid,true,false} };
	}
	return tile_map_.at(tile_coord.y * GetLevelWidth() + tile_coord.x);
}

sf::Vector2i Level::PosToCoords(const sf::Vector2f world_pos)
{
	sf::Vector2i coord;
	coord.x = std::floor(world_pos.x / TILE_SIZE);
	coord.y = std::floor(world_pos.y / TILE_SIZE);
	return coord;
}

void Level::DrawLevel(sf::RenderTarget& target)
{
	for (int y = 0; y < level_height_; y++)
	{
		for (int x = 0; x < level_width_; x++)
		{
			Tile& current_tile = tile_map_.at(x + y * level_width_);
			// Set the position of the sprite
			current_tile.sprite_.setPosition(x * TILE_SIZE, y * TILE_SIZE);
			if (current_tile.tile_type_ != TileType::kEmpty && current_tile.tile_type_ != TileType::kEmptySolid)
			{
				// Draw the sprite
				target.draw(current_tile.sprite_);
			}
		}
	}
}

void Level::SaveLevelToJson(const std::string& file_name) {
	nlohmann::json json_level;
	json_level["tiles"] = nlohmann::json::array();
	for (int y = 0; y < level_height_; y++) {
		for (int x = 0; x < level_width_; x++) {
			nlohmann::json tile;
			tile["type"] = tile_map_.at(y * level_width_ + x).tile_type_;
			tile["solid"] = tile_map_.at(y * level_width_ + x).solid_;
			tile["deadly"] = tile_map_.at(y * level_width_ + x).deadly_;

			json_level["tiles"].push_back(tile);
		}
	}

	//Writing the formatted JSON to the file
	std::ofstream file(file_name);
	file << json_level.dump(4); 
}

void Level::LoadLevelFromJson(const std::string& file_path, Texture texture) {
	std::ifstream file(file_path);
	if (file.is_open()) {
		nlohmann::json json_level;
		file >> json_level;

		int index = 0;
		for (auto& tile : json_level["tiles"]) {
			tile_map_.at(index).tile_type_ = static_cast<TileType>(tile["type"]);
			tile_map_.at(index).solid_ = tile["solid"];
			tile_map_.at(index).deadly_ = tile["deadly"];
			tile_map_.at(index).sprite_.setTexture(texture.GetTextureMap().at(tile_map_.at(index).tile_type_));
			index++;
		}
	}
	else {
		std::cout << "Save file not found" << std::endl;
	}
}

