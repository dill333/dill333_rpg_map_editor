#include "Map.h"

Map::Map()
{

	// Load the tile sheets here
	loaded = true;
	loadedTileSheet = true;

	/*// Load the tile types
	sf::Texture *tileSheetTexture = TextureManager::getTexture("tiles0.png");
	if(tileSheetTexture != NULL)
	{
		// Load the tile types
		for(int i = 0; i < NUM_TTX; i++)
		{
			for(int j = 0; j < NUM_TTY; j++)
			{
				tileTypes[i][j].setTexture(*tileSheetTexture);
				tileTypes[i][j].setTextureRect(sf::Rect<int>(i * Tile::TILE_WIDTH, j * Tile::TILE_HEIGHT, Tile::TILE_WIDTH, Tile::TILE_HEIGHT));
			}
		}
	}
	else
		loadedTileSheet = false;*/

	blockSprite.setTexture(*TextureManager::getTexture("block.png"));
	teleportSprite.setTexture(*TextureManager::getTexture("teleport.png"));

	mapName = "room1.map";

	mapTexture.create(MAP_WIDTH, MAP_HEIGHT);

	// Move the map sprite down
	mapSprite.setPosition(0, WINDOW_HEIGHT - MAP_HEIGHT);

}

void Map::save()
{

	// The file we will use
	ofstream file;
	file.open(mapName);

	// Set up all of the tiles
	for(int i = 0; i < MAP_HEIGHT / Tile::TILE_HEIGHT; i++)
		for(int j = 0; j < MAP_WIDTH / Tile::TILE_WIDTH; j++)
				file<<tiles[j][i];

	// Close the file
	file.close();

	loaded = true;

}

void Map::load(string mN)
{
	
	// Set the map name
	mapName = mN;

	// Open the file we need
	ifstream file;
	file.open(mapName);

	// Set up all of the tiles
	for(int i = 0; i < MAP_HEIGHT / Tile::TILE_HEIGHT; i++)
	{
		for(int j = 0; j < MAP_WIDTH / Tile::TILE_WIDTH; j++)
		{
			if(file.good())
				file>>tiles[j][i];
			else
			{
				// EOF too early
				file.close();
				loaded = false;
			}
		}
	}

	// Close the file
	file.close();

	updateSprite();

}

bool Map::isLoaded()
{

	return(loaded && loadedTileSheet);

}

void Map::draw(sf::RenderWindow *window)
{

	// Draw the map sprite
	window->draw(mapSprite);

}

sf::Vector2<int> Map::getPosition()
{

	return(sf::Vector2<int>(mapSprite.getPosition()));

}

void Map::replaceTileType(int tx, int ty, int ttx, int tty)
{

	tiles[tx][ty].create(tx, ty, ttx, tty, tiles[tx][ty].getProp(), tiles[tx][ty].getTeleX(), tiles[tx][ty].getTeleY());

}

void Map::flipTileBlocked(int tx, int ty)
{

	if(tiles[tx][ty].getProp() == Tile::TP_BLOCKED)
		tiles[tx][ty].create(tx, ty, tiles[tx][ty].getTileTypeX(), tiles[tx][ty].getTileTypeY(), Tile::TP_NONE);
	else
		tiles[tx][ty].create(tx, ty, tiles[tx][ty].getTileTypeX(), tiles[tx][ty].getTileTypeY(), Tile::TP_BLOCKED);

}

void Map::setTileTeleport(int tx, int ty, int telex, int teley, int tmn)
{

	if(tiles[tx][ty].getProp() == Tile::TP_TELEPORT)
		tiles[tx][ty].create(tx, ty, tiles[tx][ty].getTileTypeX(), tiles[tx][ty].getTileTypeY(), Tile::TP_NONE);
	else
		tiles[tx][ty].create(tx, ty, tiles[tx][ty].getTileTypeX(), tiles[tx][ty].getTileTypeY(), Tile::TP_TELEPORT, telex, teley, tmn);

}

void Map::updateSprite()
{

	// Clear the map
	mapTexture.clear();

	// Make sure we have a map
	if(loaded)
	{
		// Set up the map
		for(int i = 0; i < MAP_WIDTH / Tile::TILE_WIDTH; i++)
		{
			for(int j = 0; j < MAP_HEIGHT / Tile::TILE_HEIGHT; j++)
			{
				// Get tile info
				int ttx = tiles[i][j].getTileTypeX();
				int tty = tiles[i][j].getTileTypeY();
				sf::Rect<int> rect = tiles[i][j].getRect();
				sf::Sprite temp;
				if((ttx < 0) || (ttx > NUM_TTX) || (tty < 0) || (tty > NUM_TTY))
				{
					loaded = false;
					temp = *TileSpriteManager::getTileSprite(sf::Vector3<int>(0, 2, 0));
					//temp = tileTypes[2][0];
				}
				else
					temp = *TileSpriteManager::getTileSprite(sf::Vector3<int>(0, ttx, tty));

				// Make sure whoever edited this file knew what they were doing
				if(((i * Tile::TILE_WIDTH) != rect.left) || ((j * Tile::TILE_HEIGHT) != rect.top))
					loaded = false;

				// Move the sprite to where we need to draw it
				temp.setPosition(rect.left, rect.top);
				mapTexture.draw(temp);

				// If the tile is blocked, show it
				int tp = tiles[i][j].getProp();
				if(tp == Tile::TP_BLOCKED)
				{
					blockSprite.setPosition(rect.left, rect.top);
					mapTexture.draw(blockSprite);
				}
				else if(tp == Tile::TP_TELEPORT)
				{
					teleportSprite.setPosition(rect.left, rect.top);
					mapTexture.draw(teleportSprite);
				}
			}
		}
		mapTexture.display();
		mapSprite.setTexture(mapTexture.getTexture());
	}

	if(!loaded)
	{
		// Something went wrong, lets make the default map
		for(int i = 0; i < MAP_WIDTH / Tile::TILE_WIDTH; i++)
		{
			for(int j = 0; j < MAP_HEIGHT / Tile::TILE_HEIGHT; j++)
			{
				tiles[i][j].create(i, j, 1, 0, Tile::TP_NONE);
				sf::Sprite temp = *TileSpriteManager::getTileSprite(sf::Vector3<int>(0, 2, 0));
				temp.setPosition(i * Tile::TILE_WIDTH, j * Tile::TILE_HEIGHT);
				mapTexture.draw(temp);
			}
		}
		// Save over the corrupt map with the default one
		save();
	}

	mapTexture.display();
	mapSprite.setTexture(mapTexture.getTexture());

}

Map::~Map()
{
}