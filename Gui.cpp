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
	}

	mousePressedBefore = sf::Mouse::IsButtonPressed(sf::Mouse::Left);

}

void Gui::draw(sf::RenderWindow *window)
{

	// Get the mouse position
	mousePos = sf::Mouse::GetPosition(*window);

	// Draw stuff
	m.draw(window);
	window->Draw(tileSheetSprite);
	if(tileSelected || blockSelected)
		window->Draw(tileOutline);
	window->Draw(blockSprite);

}

Gui::~Gui()
{

	// Save the map
	m.save();

}
