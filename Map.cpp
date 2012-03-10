#include "Map.h"

Map::Map()
{

	// If nothing goes wrong, this will still be true at the end
	loaded = true;
	loadedTileSheet = true;

	// Open the file we need
	ifstream file;
	file.open("room1.map");

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

	// Load the tile types
	sf::Texture *tileSheetTexture = TextureManager::getTexture("tilesheet.png");
	if(tileSheetTexture != NULL)
	{
		// Load the tile types
		for(int i = 0; i < NUM_TTX; i++)
		{
			for(int j = 0; j < NUM_TTY; j++)
			{
				tileTypes[i][j].SetTexture(*tileSheetTexture);
				tileTypes[i][j].SetSubRect(sf::Rect<int>(i * Tile::TILE_WIDTH, j * Tile::TILE_HEIGHT, Tile::TILE_WIDTH, Tile::TILE_HEIGHT));
			}
		}
	}
	else
		loadedTileSheet = false;

	// Set up the map texture
	mapTexture.Create(MAP_WIDTH, MAP_HEIGHT);
	mapTexture.Clear();

	blockSprite.SetTexture(*TextureManager::getTexture("block.png"));

	if(loaded)
	{
		for(int i = 0; i < MAP_WIDTH / Tile::TILE_WIDTH; i++)
		{
			for(int j = 0; j < MAP_HEIGHT / Tile::TILE_HEIGHT; j++)
			{
				// Get tile info
				int ttx = tiles[i][j].getTileTypeX();
				int tty = tiles[i][j].getTileTypeY();
				sf::Rect<int> rect = tiles[i][j].getRect();
				sf::Sprite temp = tileTypes[ttx][tty];

				// Make sure whoever edited this file knew what they were doing
				if(((i * Tile::TILE_WIDTH) != rect.Left) || ((j * Tile::TILE_HEIGHT) != rect.Top))
					loaded = false;

				// Move the sprite to where we need to draw it
				temp.SetPosition(rect.Left, rect.Top);
				mapTexture.Draw(temp);

				// If the tile is blocked, show it
				int tp = tiles[i][j].getProp();
				if(tp == Tile::TP_BLOCKED)
				{
					blockSprite.SetPosition(rect.Left, rect.Top);
					mapTexture.Draw(blockSprite);
				}
			}
		}
		mapTexture.Display();
		mapSprite.SetTexture(mapTexture.GetTexture());
	}

	if(!loaded)
	{
		// Something went wrong, lets make the default map
		for(int i = 0; i < MAP_WIDTH / Tile::TILE_WIDTH; i++)
		{
			for(int j = 0; j < MAP_HEIGHT / Tile::TILE_HEIGHT; j++)
			{
				tiles[i][j].create(i, j, 2, 0, Tile::TP_NONE);
				sf::Sprite temp = tileTypes[2][0];
				temp.SetPosition(i * Tile::TILE_WIDTH, j * Tile::TILE_HEIGHT);
				mapTexture.Draw(temp);
			}
		}
		// Save over the corrupt map with the default one
		save();
	}

	mapTexture.Display();
	mapSprite.SetTexture(mapTexture.GetTexture());

	// Move the map sprite down
	mapSprite.SetY(WINDOW_HEIGHT - MAP_HEIGHT);

}

void Map::save()
{

	// The file we will use
	ofstream file;
	file.open("room1.map");

	// Set up all of the tiles
	for(int i = 0; i < MAP_HEIGHT / Tile::TILE_HEIGHT; i++)
		for(int j = 0; j < MAP_WIDTH / Tile::TILE_WIDTH; j++)
				file<<tiles[j][i];

	// Close the file
	file.close();

	loaded = true;

}

bool Map::isLoaded()
{

	return(loaded && loadedTileSheet);

}

void Map::draw(sf::RenderWindow *window)
{

	// Draw the map sprite
	window->Draw(mapSprite);

}

sf::Vector2<int> Map::getPosition()
{

	return(sf::Vector2<int>(mapSprite.GetPosition()));

}

void Map::replaceTileType(int tx, int ty, int ttx, int tty)
{

	tiles[tx][ty].create(tx, ty, ttx, tty, tiles[tx][ty].getProp());

}

void Map::flipTileBlocked(int tx, int ty)
{

	if(tiles[tx][ty].getProp() == Tile::TP_BLOCKED)
		tiles[tx][ty].create(tx, ty, tiles[tx][ty].getTileTypeX(), tiles[tx][ty].getTileTypeY(), Tile::TP_NONE);
	else
		tiles[tx][ty].create(tx, ty, tiles[tx][ty].getTileTypeX(), tiles[tx][ty].getTileTypeY(), Tile::TP_BLOCKED);

}

void Map::updateSprite()
{

	// Redraw the sprite
	mapTexture.Clear();

	for(int i = 0; i < MAP_WIDTH / Tile::TILE_WIDTH; i++)
	{
		for(int j = 0; j < MAP_HEIGHT / Tile::TILE_HEIGHT; j++)
		{
			// Get tile info
			int ttx = tiles[i][j].getTileTypeX();
			int tty = tiles[i][j].getTileTypeY();
			sf::Rect<int> rect = tiles[i][j].getRect();
			sf::Sprite temp = tileTypes[ttx][tty];

			// Move the sprite to where we need to draw it
			temp.SetPosition(rect.Left, rect.Top);
			mapTexture.Draw(temp);

			// If the tile is blocked, show it
			int tp = tiles[i][j].getProp();
			if(tp == Tile::TP_BLOCKED)
			{
				blockSprite.SetPosition(rect.Left, rect.Top);
				mapTexture.Draw(blockSprite);
			}
		}
	}
	mapTexture.Display();
	mapSprite.SetTexture(mapTexture.GetTexture());

	// Move the map sprite down
	mapSprite.SetY(WINDOW_HEIGHT - MAP_HEIGHT);

}

Map::~Map()
{
}