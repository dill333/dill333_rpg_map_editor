#pragma once

#include "TextureManager.h"
#include "Tile.h"

class Map
{
	static const int MAP_WIDTH = 800;
	static const int MAP_HEIGHT = 640;
	static const int NUM_TTX = 4;
	static const int NUM_TTY = 4;
	sf::Sprite tileTypes[NUM_TTX][NUM_TTY];
	sf::RenderTexture mapTexture;
	sf::Sprite mapSprite;
	sf::Sprite blockSprite;
	Tile tiles[MAP_WIDTH / Tile::TILE_WIDTH][MAP_HEIGHT / Tile::TILE_HEIGHT];
	bool loaded;
	bool loadedTileSheet;
public:
	static const int WINDOW_WIDTH = 960;
	static const int WINDOW_HEIGHT = 768;
	Map();
	void save();
	bool isLoaded();
	void draw(sf::RenderWindow *window);
	sf::Vector2<int> getPosition();
	void replaceTileType(int tx, int ty, int ttx, int tty);
	void flipTileBlocked(int tx, int ty);
	void updateSprite();
	~Map();
};