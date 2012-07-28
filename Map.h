#ifndef MAP_H
#define MAP_H

#include "TextureManager.h"
#include "TileSpriteManager.h"
#include "Tile.h"
#include <string>
#include <iostream>

using namespace std;

class Map
{
	static const int MAP_WIDTH = 800;
	static const int MAP_HEIGHT = 640;
	static const int NUM_TTX = 8;
	static const int NUM_TTY = 23;
	static const int NUM_TILE_SHEETS = 25;
	static const int NUM_LAYERS = 2;
	sf::RenderTexture mapTexture;
	sf::Sprite mapSprite;
	sf::Sprite blockSprite;
	sf::Sprite teleportSprite;
	sf::Sprite pspawnSprite;
	sf::Sprite mspawnSprite;
	Tile tiles[NUM_LAYERS][MAP_WIDTH / Tile::TILE_WIDTH][MAP_HEIGHT / Tile::TILE_HEIGHT];
	bool loaded;
	bool loadedTileSheet;
	string mapName;
public:
	static const int WINDOW_WIDTH = 960;
	static const int WINDOW_HEIGHT = 768;
	Map();
	void load(string mN);
	void save();
	bool isLoaded();
	void draw(sf::RenderWindow *window);
	sf::Vector2<int> getPosition();
	void replaceTileType(int tl, int tx, int ty, int tsn, int ttx, int tty);
	void flipTileBlocked(int tx, int ty);
	void setTileTeleport(int tx, int ty, int telex, int teley, int tmn);
	void setTilePSpawn(int tx, int ty);
	void setTileMSpawn(int tx, int ty);
	void updateSprite();
	~Map();
};

#endif