#include "Texture.h"

#include "Interactive.h"

// Definitions for static members

// Definitions for static members
sf::Texture Texture::empty_;
sf::Texture Texture::dirt_;
sf::Texture Texture::grass_;

std::vector <sf::Texture> Texture::checkpoint_;
sf::Texture Texture::coin_;
sf::Texture Texture::diamond_;
std::vector <sf::Texture> Texture::floating_spike_;
std::vector <sf::Texture> Texture::grounded_spike_;
sf::Texture Texture::star_;


sf::Texture Texture::background_texture_;

std::map<TileType, sf::Texture> Texture::tile_type_to_texture_;
std::map<InteractiveType, sf::Texture> Texture::interact_type_to_texture_;

void Texture::LoadTextures() {
	grass_.loadFromFile("data/sprites/tiles/grassMid.png");
	dirt_.loadFromFile("data/sprites/tiles/grassCenter.png");

	sf::Texture temp_texture;
	// Loading files as textures
	temp_texture.loadFromFile("data/sprites/interactives/flagRed_down.png");
	checkpoint_.push_back(temp_texture);
	temp_texture.loadFromFile("data/sprites/interactives/flagRed1.png");
	checkpoint_.push_back(temp_texture);
	temp_texture.loadFromFile("data/sprites/interactives/flagRed2.png");
	checkpoint_.push_back(temp_texture);
	temp_texture.loadFromFile("data/sprites/interactives/saw.png");
	floating_spike_.push_back(temp_texture);
	temp_texture.loadFromFile("data/sprites/interactives/saw_move.png");
	floating_spike_.push_back(temp_texture);
	temp_texture.loadFromFile("data/sprites/interactives/sawHalf.png");
	grounded_spike_.push_back(temp_texture);
	temp_texture.loadFromFile("data/sprites/interactives/sawHalf_move.png");
	grounded_spike_.push_back(temp_texture);

	coin_.loadFromFile("data/sprites/interactives/coinGold.png");
	diamond_.loadFromFile("data/sprites/interactives/gemBlue.png");
	star_.loadFromFile("data/sprites/interactives/star.png");

	background_texture_.loadFromFile("data/sprites/backgrounds/colored_grass.png");

	tile_type_to_texture_ = {};
	tile_type_to_texture_[TileType::kEmpty] = empty_;
	tile_type_to_texture_[TileType::kEmptySolid] = empty_;
	tile_type_to_texture_[TileType::kGrass] = grass_;
	tile_type_to_texture_[TileType::kDirt] = dirt_;

	interact_type_to_texture_ = {};
	interact_type_to_texture_[InteractiveType::kEmpty] = empty_;
	interact_type_to_texture_[InteractiveType::kCheckpoint] = checkpoint_[0];
	interact_type_to_texture_[InteractiveType::kCoin] = coin_;
	interact_type_to_texture_[InteractiveType::kDiamond] = diamond_;
	interact_type_to_texture_[InteractiveType::kFloatingSpikes] = floating_spike_[0];
	interact_type_to_texture_[InteractiveType::kSpikes] = grounded_spike_[0];
	interact_type_to_texture_[InteractiveType::kStar] = star_;
}