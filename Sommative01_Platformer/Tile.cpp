#include "Tile.h"

Tile::Tile()
{
    tile_type_ = TileType::kEmpty;
    solid_ = false;
    deadly_ = false;
    //sf::Texture default_texture;
    //default_texture.loadFromFile("data/sprites/tiles/empty.png");
    //sprite_.setTexture(default_texture);
}

Tile::Tile(const TileType type, const bool solid, const bool deadly)
{
    tile_type_ = type;
    solid_ = solid;
    deadly_ = deadly;
}


