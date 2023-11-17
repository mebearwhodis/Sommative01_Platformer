#include "Texture.h"

#include "Interactive.h"

// Definitions for static members

// Definitions for static members
sf::Texture Texture::empty_;
sf::Texture Texture::dirt_;
sf::Texture Texture::grass_;

sf::Texture Texture::checkpoint_down_;
sf::Texture Texture::checkpoint_up1_;
sf::Texture Texture::checkpoint_up2_;
sf::Texture Texture::coin_;
sf::Texture Texture::diamond_;
sf::Texture Texture::floating_spike1_;
sf::Texture Texture::floating_spike2_;
sf::Texture Texture::spike1_;
sf::Texture Texture::spike2_;
sf::Texture Texture::star_;


sf::Texture Texture::background_texture_;

std::map<TileType, sf::Texture> Texture::tile_type_to_texture_;
std::map<InteractiveType, sf::Texture> Texture::interact_type_to_texture_;
//{ {TileType::kEmpty, empty_}, {TileType::kEmptySolid, empty_}, {TileType::kGrass, grass_}, {TileType::kDirt, dirt_} }

void Texture::LoadTextures() {
	//empty_.loadFromFile("data/sprites/tiles/empty.png");
	grass_.loadFromFile("data/sprites/tiles/grassMid.png");
	dirt_.loadFromFile("data/sprites/tiles/grassCenter.png");

	checkpoint_down_.loadFromFile("data/sprites/interactives/flagRed_down.png");
	checkpoint_up1_.loadFromFile("data/sprites/interactives/flagRed1.png");
	checkpoint_up2_.loadFromFile("data/sprites/interactives/flagRed2.png");
	coin_.loadFromFile("data/sprites/interactives/coinGold.png");
	diamond_.loadFromFile("data/sprites/interactives/gemBlue.png");
	floating_spike1_.loadFromFile("data/sprites/interactives/saw.png");
	floating_spike2_.loadFromFile("data/sprites/interactives/saw_move.png");
	spike1_.loadFromFile("data/sprites/interactives/sawHalf.png");
	spike2_.loadFromFile("data/sprites/interactives/sawHalf_move.png");
	star_.loadFromFile("data/sprites/interactives/star.png");

	background_texture_.loadFromFile("data/sprites/backgrounds/blue_desert.png");

	tile_type_to_texture_ = {};
	tile_type_to_texture_[TileType::kEmpty] = empty_;
	tile_type_to_texture_[TileType::kEmptySolid] = empty_;
	tile_type_to_texture_[TileType::kGrass] = grass_;
	tile_type_to_texture_[TileType::kDirt] = dirt_;

	interact_type_to_texture_ = {};
	interact_type_to_texture_[InteractiveType::kEmpty] = empty_;
	interact_type_to_texture_[InteractiveType::kCheckpoint] = checkpoint_down_;
	interact_type_to_texture_[InteractiveType::kCheckpointUp] = checkpoint_up1_;
	interact_type_to_texture_[InteractiveType::kCheckpointUp] = checkpoint_up2_;
	interact_type_to_texture_[InteractiveType::kCoin] = coin_;
	interact_type_to_texture_[InteractiveType::kDiamond] = diamond_;
	interact_type_to_texture_[InteractiveType::kFloatingSpikes] = floating_spike1_;
	interact_type_to_texture_[InteractiveType::kFloatingSpikes] = floating_spike2_;
	interact_type_to_texture_[InteractiveType::kSpikes] = spike1_;
	interact_type_to_texture_[InteractiveType::kSpikes] = spike2_;
	interact_type_to_texture_[InteractiveType::kStar] = star_;
}