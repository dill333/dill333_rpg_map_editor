#include "Map.h"

bool Map::loadTileSheet()
{

	// Load the tile sheet
	if(tileSheet.LoadFromFile("tilesheet.png"))
	{
		// Cut up the tile sprites
		for(int i = 0; i < 6; i++)
		{
			tileTypes[i].SetTexture(tileSheet);
			tileTypes[i].SetSubRect(sf::Rect<int>(i * TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));
		}
		return true;
	}
	else
		return false;

}

bool Map::loadMap()
{

	// Open the file
	ifstream file;
	file.open("room1.map");

	// Set up all of the tiles
	for(int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 25; j++)
		{
			if(file.good())
				file>>tiles[j][i];
			else
			{
				// EOF too early
				file.close();
				return loadDefaultMap();
			}
		}
	}

	// Close the file
	file.close();

	return true;

}

bool Map::loadDefaultMap()
{

	// Set up all of the tiles
	for(int i = 0; i < 20; i++)
		for(int j = 0; j < 25; j++)
			tiles[j][i] = Tile(j * 32, i * 32, tt_grass, false);

	return save();

}

Map::Map()
{

	// Initialize
	loaded = loadTileSheet();
	loaded &= loadMap();
	loaded &= mapTexture.Create(800, 640);

	// Clear the map texture
	mapTexture.Clear();

	// Draw all of the tiles to the texture
	for(int i = 0; i < 25; i++)
	{
		for(int j = 0; j < 20; j++)
		{
			int tt = tiles[i][j].getTileType();
			sf::Sprite temp = tileTypes[tt];
			temp.SetX(i * 32);
			temp.SetY(j * 32);
			mapTexture.Draw(temp);
		}
	}
	
	// Done drawing, make the texture visible
	mapTexture.Display();

	// Set up the map sprite
	mapSprite = sf::Sprite(mapTexture.GetTexture());
	mapSprite.SetY(128);

}

bool Map::getLoaded()
{

	return loaded;

}

void Map::draw(sf::RenderWindow& window)
{

	// Draw the map
	window.Draw(mapSprite);

}

bool Map::save()
{

	ofstream file;
	file.open("room1.map");

	for(int i = 0; i < 20; i++)
		for(int j = 0; j < 25; j++)
			file<<tiles[j][i];

	file.close();

	return true;

}

Map::~Map()
{
}
