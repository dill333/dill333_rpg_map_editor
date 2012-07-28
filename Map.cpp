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
	pspawnSprite.setTexture(*TextureManager::getTexture("pspawn.png"));
	mspawnSprite.setTexture(*TextureManager::getTexture("mspawn.png"));

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
			for(int k = 0; k < NUM_LAYERS; k++)
				file<<tiles[k][j][i];

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
			for(int k = 0; k < NUM_LAYERS; k++)
			{
				if(file.good())
					file>>tiles[k][j][i];
				else
				{
					// EOF too early
					file.close();
					loaded = false;
				}
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

void Map::replaceTileType(int tl, int tx, int ty, int tsn, int ttx, int tty)
{

	tiles[tl][tx][ty].create(tsn, tx, ty, ttx, tty, tiles[tl][tx][ty].getProp(), tiles[tl][tx][ty].getTeleX(), tiles[tl][tx][ty].getTeleY());

}

void Map::flipTileBlocked(int tx, int ty)
{

	if(tiles[0][tx][ty].getProp() == Tile::TP_BLOCKED)
		tiles[0][tx][ty].create(tiles[0][tx][ty].getTileSheetNum(), tx, ty, tiles[0][tx][ty].getTileTypeX(), tiles[0][tx][ty].getTileTypeY(), Tile::TP_NONE);
	else
		tiles[0][tx][ty].create(tiles[0][tx][ty].getTileSheetNum(), tx, ty, tiles[0][tx][ty].getTileTypeX(), tiles[0][tx][ty].getTileTypeY(), Tile::TP_BLOCKED);

}

void Map::setTileTeleport(int tx, int ty, int telex, int teley, int tmn)
{

	if(tiles[0][tx][ty].getProp() == Tile::TP_TELEPORT)
		tiles[0][tx][ty].create(tiles[0][tx][ty].getTileSheetNum(), tx, ty, tiles[0][tx][ty].getTileTypeX(), tiles[0][tx][ty].getTileTypeY(), Tile::TP_NONE);
	else
		tiles[0][tx][ty].create(tiles[0][tx][ty].getTileSheetNum(), tx, ty, tiles[0][tx][ty].getTileTypeX(), tiles[0][tx][ty].getTileTypeY(), Tile::TP_TELEPORT, telex, teley, tmn);

}

void Map::setTilePSpawn(int tx, int ty)
{

	// Get rid of other pspawn
	for(int i = 0; i < MAP_WIDTH / Tile::TILE_WIDTH; i++)
	{
		for(int j = 0; j < MAP_HEIGHT / Tile::TILE_HEIGHT; j++)
		{
			if(tiles[0][i][j].getProp() == Tile::TP_PSPAWN)
				tiles[0][i][j].create(tiles[0][i][j].getTileSheetNum(), i, j, tiles[0][i][j].getTileTypeX(), tiles[0][i][j].getTileTypeY(), Tile::TP_NONE);
		}
	}

	tiles[0][tx][ty].create(tiles[0][tx][ty].getTileSheetNum(), tx, ty, tiles[0][tx][ty].getTileTypeX(), tiles[0][tx][ty].getTileTypeY(), Tile::TP_PSPAWN);

}
void Map::setTileMSpawn(int tx, int ty)
{

	if(tiles[0][tx][ty].getProp() == Tile::TP_MSPAWN)
		tiles[0][tx][ty].create(tiles[0][tx][ty].getTileSheetNum(), tx, ty, tiles[0][tx][ty].getTileTypeX(), tiles[0][tx][ty].getTileTypeY(), Tile::TP_NONE);
	else
		tiles[0][tx][ty].create(tiles[0][tx][ty].getTileSheetNum(), tx, ty, tiles[0][tx][ty].getTileTypeX(), tiles[0][tx][ty].getTileTypeY(), Tile::TP_MSPAWN);

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
				for(int k = 0; k < NUM_LAYERS; k++)
				{
					// Get tile info
					int tsn = tiles[k][i][j].getTileSheetNum();
					int ttx = tiles[k][i][j].getTileTypeX();
					int tty = tiles[k][i][j].getTileTypeY();
					sf::Rect<int> rect = tiles[k][i][j].getRect();
					sf::Sprite temp;
					if((tsn < 0) || (tsn > NUM_TILE_SHEETS) || (ttx < 0) || (ttx > NUM_TTX) || (tty < 0) || (tty > NUM_TTY))
					{
						loaded = false;
						temp = *TileSpriteManager::getTileSprite(sf::Vector3<int>(0, 1, 0));
					}
					else
						temp = *TileSpriteManager::getTileSprite(sf::Vector3<int>(tsn, ttx, tty));

					// Make sure whoever edited this file knew what they were doing
					if(((i * Tile::TILE_WIDTH) != rect.left) || ((j * Tile::TILE_HEIGHT) != rect.top))
						loaded = false;

					// Move the sprite to where we need to draw it
					temp.setPosition(rect.left, rect.top);
					mapTexture.draw(temp);
				}
			}
		}
		// Must draw the block/teleport/spawns sprite separately
		for(int i = 0; i < MAP_WIDTH / Tile::TILE_WIDTH; i++)
		{
			for(int j = 0; j < MAP_HEIGHT / Tile::TILE_HEIGHT; j++)
			{
				int tp = tiles[0][i][j].getProp();
				sf::Rect<int> rect = tiles[0][i][j].getRect();
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
				else if(tp == Tile::TP_PSPAWN)
				{
					pspawnSprite.setPosition(rect.left, rect.top);
					mapTexture.draw(pspawnSprite);
				}
				else if(tp == Tile::TP_MSPAWN)
				{
					mspawnSprite.setPosition(rect.left, rect.top);
					mapTexture.draw(mspawnSprite);
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
				tiles[0][i][j].create(0, i, j, 1, 0, Tile::TP_NONE);
				tiles[1][i][j].create(0, i, j, 0, 0, Tile::TP_NONE);
				sf::Sprite temp1 = *TileSpriteManager::getTileSprite(sf::Vector3<int>(0, 1, 0));
				sf::Sprite temp2 = *TileSpriteManager::getTileSprite(sf::Vector3<int>(0, 0, 0));
				temp1.setPosition(i * Tile::TILE_WIDTH, j * Tile::TILE_HEIGHT);
				temp2.setPosition(i * Tile::TILE_WIDTH, j * Tile::TILE_HEIGHT);
				mapTexture.draw(temp1);
				mapTexture.draw(temp2);
			}
		}
		tiles[0][0][0].create(0, 0, 0, 1, 0, Tile::TP_PSPAWN);
		// Save over the corrupt map with the default one
		save();
		loaded = true;
	}

	mapTexture.display();
	mapSprite.setTexture(mapTexture.getTexture());

}

Map::~Map()
{
}