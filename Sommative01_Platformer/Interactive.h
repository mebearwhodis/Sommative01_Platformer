#pragma once
#include "Tile.h"

enum class InteractiveType
{
	kEmpty,
	kCheckpoint,
	kCoin,
	kDiamond,
	kFloatingSpikes,
	kSpikes,
	kStar
};
class Interactive
{
public:
    int size_ = TILE_SIZE;

    InteractiveType interactive_type_;
    sf::Sprite sprite_;

	bool temporary_;
    bool deadly_;
	bool taken_;

	Interactive();
	Interactive(InteractiveType type, bool temporary, bool deadly);
};
