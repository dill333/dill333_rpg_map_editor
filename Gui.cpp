#include "Gui.h"

Gui::Gui()
{

	tileSheetSprite.SetTexture(*TextureManager::getTexture("tilesheet.png"));
	tileSheetSprite.SetX(MAP_WIDTH + ((Map::WINDOW_WIDTH - MAP_WIDTH - 128) / 2));
	tileSheetSprite.SetY(Map::WINDOW_HEIGHT - MAP_HEIGHT);
	tileSelected = false;
	blockSelected = false;
	drawBox.Width = Tile::TILE_WIDTH;
	drawBox.Height = Tile::TILE_HEIGHT;
	mousePos.x = 0;
	mousePos.y = 0;
	mapRect.Left = m.getPosition().x;
	mapRect.Top = m.getPosition().y;
	mapRect.Width = MAP_WIDTH;
	mapRect.Height = MAP_HEIGHT;
	tileSheetRect.Left = tileSheetSprite.GetPosition().x;
	tileSheetRect.Top = tileSheetSprite.GetPosition().y;
	tileSheetRect.Width = 128;
	tileSheetRect.Height = 128;
	tileTypeSelectedX = 0;
	tileTypeSelectedY = 0;
	blockSprite.SetTexture(*TextureManager::getTexture("block.png"));
	blockSprite.SetPosition(32, 32);
	blockRect.Left = blockSprite.GetPosition().x;
	blockRect.Top = blockSprite.GetPosition().y;
	blockRect.Width = 32;
	blockRect.Height = 32;
	tileOutline.SetTexture(*TextureManager::getTexture("tileoutline.png"));
	mousePressedBefore = false;
	arrowLeft.SetTexture(*TextureManager::getTexture("arrowleft.png"));
	arrowLeft.SetPosition(128, 32);
	arrowLeftRect.Left = arrowLeft.GetPosition().x;
	arrowLeftRect.Top = arrowLeft.GetPosition().y;
	arrowLeftRect.Width = 32;
	arrowLeftRect.Height = 32;
	arrowRight.SetTexture(*TextureManager::getTexture("arrowright.png"));
	arrowRight.SetPosition(192, 32);
	arrowRightRect.Left = arrowRight.GetPosition().x;
	arrowRightRect.Top = arrowRight.GetPosition().y;
	arrowRightRect.Width = 32;
	arrowRightRect.Height = 32;
	mapNum = 1;
	m.load("room1.map");
	loaded = m.isLoaded();
	saveSprite.SetTexture(*TextureManager::getTexture("save.png"));
	saveSprite.SetPosition(64, 32);
	saveSpriteRect.Left = saveSprite.GetPosition().x;
	saveSpriteRect.Top = saveSprite.GetPosition().y;
	saveSpriteRect.Width = 32;
	saveSpriteRect.Height = 32;

	for(int i = 0; i < NUM_MAPS; i++)
	{
		numbers[i].SetTexture(*TextureManager::getTexture("numbers.png"));
		numbers[i].SetSubRect(sf::Rect<int>(i * 32, 0, 32, 32));
		numbers[i].SetPosition(160, 32);
	}

}

bool Gui::isLoaded()
{

	return loaded;

}

void Gui::tick()
{

	// If the mouse was pressed before but now has been released
	if(mousePressedBefore && !sf::Mouse::IsButtonPressed(sf::Mouse::Left))
	{
		if(mapRect.Contains(mousePos))
		{
			// User selected a tile on the map
			// Replace that tile with the one they selected earlier, if they did
			if(tileSelected)
			{
				m.replaceTileType(mousePos.x / 32, (mousePos.y - mapRect.Top) / 32, tileTypeSelectedX, tileTypeSelectedY);
				m.updateSprite();
			}
			else if(blockSelected)
			{
				m.flipTileBlocked(mousePos.x / 32, (mousePos.y - mapRect.Top) / 32);
				m.updateSprite();
			}
		}
		else if(tileSheetRect.Contains(mousePos))
		{
			// User selected a tile in the tile sheet
			tileSelected = true;
			blockSelected = false;
			tileOutline.SetX((((mousePos.x - tileSheetRect.Left) / 32) * 32) + tileSheetRect.Left);
			tileOutline.SetY((((mousePos.y - tileSheetRect.Top) / 32) * 32) + tileSheetRect.Top);

			// Determine which tile they selected
			tileTypeSelectedX = (mousePos.x - tileSheetRect.Left) / 32;
			tileTypeSelectedY = (mousePos.y - tileSheetRect.Top) / 32;
		}
		else if(blockRect.Contains(mousePos))
		{
			// User selected the block
			blockSelected = true;
			tileSelected = false;
			tileOutline.SetPosition(blockRect.Left, blockRect.Top);
		}
		else
			tileSelected = false;

		if(arrowLeftRect.Contains(mousePos) && (mapNum > 1))
		{
			mapNum--;
			changeMaps();
		}
		else if(arrowRightRect.Contains(mousePos) && (mapNum < NUM_MAPS))
		{
			mapNum++;
			changeMaps();
		}
		else if(saveSpriteRect.Contains(mousePos))
		{
			m.save();
			cout<<"Saved map.\n";
		}
	}

	mousePressedBefore = sf::Mouse::IsButtonPressed(sf::Mouse::Left);

}

void Gui::changeMaps()
{

	stringstream s;
	s<<"room"<<mapNum<<".map";
	m.load(s.str());

}

void Gui::draw(sf::RenderWindow *window)
{

	// Get the mouse position
	mousePos = sf::Mouse::GetPosition(*window);

	// Draw stuff
	m.draw(window);
	window->Draw(tileSheetSprite);
	window->Draw(blockSprite);
	window->Draw(arrowLeft);
	window->Draw(arrowRight);
	window->Draw(numbers[mapNum - 1]);
	window->Draw(saveSprite);

	if(tileSelected || blockSelected)
		window->Draw(tileOutline);

}

Gui::~Gui()
{



}
