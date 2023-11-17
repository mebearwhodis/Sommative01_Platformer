#include "Level.h"
#include "Texture.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

sf::Vector2f Level::respawn_point_ = sf::Vector2f(TILE_SIZE * 7 + TILE_SIZE / 2, TILE_SIZE * 2);
int Level::level_width_ = 100;
int Level::level_height_ = 10;

Tile Level::tile_map_[1000] = {Tile{TileType::kEmpty, false, false}};
Interactive Level::interact_map_[1000] = {Interactive{InteractiveType::kEmpty, false, false}};


Tile Level::GetTileAt(const sf::Vector2i tile_coord)
{
	if (tile_coord.x < 0 || tile_coord.y < 0 || tile_coord.x >= GetLevelWidth() || tile_coord.y >= GetLevelHeight())
	{
		return { Tile{TileType::kEmptySolid,true,false} };
	}
	return tile_map_[tile_coord.y * GetLevelWidth() + tile_coord.x];
}

TileType Level::GetTileTypeAt(const sf::Vector2i tile_coord)
{
	if (tile_coord.x < 0 || tile_coord.y < 0 || tile_coord.x >= GetLevelWidth() || tile_coord.y >= GetLevelHeight())
	{
		return TileType::kEmptySolid;
	}
	return tile_map_[tile_coord.y * GetLevelWidth() + tile_coord.x].tile_type_;
}

sf::Vector2i Level::PosToCoords(const sf::Vector2f world_pos)
{
	sf::Vector2i coord;
	coord.x = static_cast<int>(std::floor(world_pos.x / TILE_SIZE));
	coord.y = static_cast<int>(std::floor(world_pos.y / TILE_SIZE));
	return coord;
}

//sprite_.setTexture(Texture::GetTileTextureFromType(type));
void Level::DrawLevel(sf::RenderTarget& target)
{
	for (int y = 0; y < GetLevelHeight(); y++)
	{
		for (int x = 0; x < GetLevelWidth(); x++)
		{
			Tile& current_tile = tile_map_[x + y * GetLevelWidth()];
			Interactive& current_interactive = interact_map_[x + y * GetLevelWidth()];
			// Set the position of the sprite
			if (current_tile.tile_type_ != TileType::kEmpty && current_tile.tile_type_ != TileType::kEmptySolid)
			{
				// Draw the sprite
				current_tile.sprite_.setPosition(static_cast<float>(x) * TILE_SIZE, static_cast<float>(y) * TILE_SIZE);
				target.draw(current_tile.sprite_);
				
			}
			if (current_interactive.interactive_type_ != InteractiveType::kEmpty && !current_interactive.taken_)
			{
				// Draw the sprite
				current_interactive.sprite_.setPosition(static_cast<float>(x) * TILE_SIZE, static_cast<float>(y) * TILE_SIZE);
				target.draw(current_interactive.sprite_);

			}
		}
	}
}

void Level::SaveLevelToJson(const std::string& file_name)
{
    nlohmann::json json_level;
    json_level["tiles"] = nlohmann::json::array();
    json_level["interactives"] = nlohmann::json::array();

    for (int y = 0; y < GetLevelHeight(); y++) {
        for (int x = 0; x < GetLevelWidth(); x++) {
            nlohmann::json tile;
            tile["type"] = tile_map_[y * GetLevelWidth() + x].tile_type_;
            tile["solid"] = tile_map_[y * GetLevelWidth() + x].solid_;
            tile["deadly"] = tile_map_[y * GetLevelWidth() + x].deadly_;
            json_level["tiles"].push_back(tile);

            nlohmann::json interactive;
            interactive["type"] = interact_map_[y * GetLevelWidth() + x].interactive_type_;
            interactive["temporary"] = interact_map_[y * GetLevelWidth() + x].temporary_;
            interactive["deadly"] = interact_map_[y * GetLevelWidth() + x].deadly_;
            interactive["taken"] = interact_map_[y * GetLevelWidth() + x].taken_;
            json_level["interactives"].push_back(interactive);
        }
    }

    // Writing the formatted JSON to the file
    std::ofstream file(file_name);
    file << json_level.dump(4);
    file.close();
}

void Level::LoadLevelFromJson(const std::string& file_name) {

    std::ifstream file(file_name);
    if (file.is_open()) {
        nlohmann::json json_level;
        file >> json_level;

        int index = 0;
        for (auto& tile : json_level["tiles"]) {
            tile_map_[index].tile_type_ = static_cast<TileType>(tile["type"]);
            tile_map_[index].solid_ = tile["solid"];
            tile_map_[index].deadly_ = tile["deadly"];
            tile_map_[index].sprite_.setTexture(Texture::tile_type_to_texture_.at(tile_map_[index].tile_type_));
            index++;
        }

        index = 0;
        for (auto& interactive : json_level["interactives"]) {
            interact_map_[index].interactive_type_ = static_cast<InteractiveType>(interactive["type"]);
            interact_map_[index].temporary_ = interactive["temporary"];
            interact_map_[index].deadly_ = interactive["deadly"];
            interact_map_[index].taken_ = interactive["taken"];
            interact_map_[index].sprite_.setTexture(Texture::interact_type_to_texture_.at(interact_map_[index].interactive_type_));
            index++;
        }
    }
    else {
        std::cout << "Save file not found" << std::endl;
    }
    file.close();
}


