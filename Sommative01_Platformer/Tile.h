#pragma once
#include <SFML/Graphics.hpp>

#define TILE_SIZE 128

enum class TileType {
    kEmpty = 0,
    kEmptySolid,
    kGrass,
    kDirt,
    // kLadder,
    // kSpikes,
    // kNPC,
    kStart,
    kCheckpoint,
    kEnd
};

class Tile
{
public:
    int size_ = TILE_SIZE;

    TileType tile_type_;
    sf::Sprite sprite_;

    bool solid_;
    bool deadly_;

    Tile();
    Tile(TileType type, bool solid, bool deadly);
};

