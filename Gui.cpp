#include "Gui.h"

Gui::Gui()
{

	tileSelected = false;
	blockSelected = false;
	teleportSelected = false;
	drawBox.width = Tile::TILE_WIDTH;
	drawBox.height = Tile::TILE_HEIGHT;
	mousePos.x = 0;
	mousePos.y = 0;
	mapRect.left = m.getPosition().x;
	mapRect.top = m.getPosition().y;
	mapRect.width = MAP_WIDTH;
	mapRect.height = MAP_HEIGHT;
	tileTypeSelectedX = 0;
	tileTypeSelectedY = 0;
	blockSprite.setTexture(*TextureManager::getTexture("block.png"));
	blockSprite.setPosition(32, 32);
	blockRect.left = blockSprite.getPosition().x;
	blockRect.top = blockSprite.getPosition().y;
	blockRect.width = 32;
	blockRect.height = 32;
	tileOutline.setTexture(*TextureManager::getTexture("tileoutline.png"));
	mousePressedBefore = false;
	arrowLeft.setTexture(*TextureManager::getTexture("arrowleft.png"));
	arrowLeft.setPosition(128, 32);
	arrowLeftRect.left = arrowLeft.getPosition().x;
	arrowLeftRect.top = arrowLeft.getPosition().y;
	arrowLeftRect.width = 32;
	arrowLeftRect.height = 32;
	arrowRight.setTexture(*TextureManager::getTexture("arrowright.png"));
	arrowRight.setPosition(192, 32);
	arrowRightRect.left = arrowRight.getPosition().x;
	arrowRightRect.top = arrowRight.getPosition().y;
	arrowRightRect.width = 32;
	arrowRightRect.height = 32;
	mapNum = 1;
	m.load("room1.map");
	loaded = m.isLoaded();
	saveSprite.setTexture(*TextureManager::getTexture("save.png"));
	saveSprite.setPosition(96, 32);
	saveSpriteRect.left = saveSprite.getPosition().x;
	saveSpriteRect.top = saveSprite.getPosition().y;
	saveSpriteRect.width = 32;
	saveSpriteRect.height = 32;
	teleportSprite.setTexture(*TextureManager::getTexture("teleport.png"));
	teleportSprite.setPosition(64, 32);
	teleportRect.left = teleportSprite.getPosition().x;
	teleportRect.top = teleportSprite.getPosition().y;
	teleportRect.width = 32;
	teleportRect.height = 32;
	teleX = 0;
	teleY = 0;
	xSprite.setTexture(*TextureManager::getTexture("x.png"));
	xSprite.setPosition(512, 0);
	ySprite.setTexture(*TextureManager::getTexture("y.png"));
	ySprite.setPosition(608, 0);
	arrowLeftXRect.left = 480;
	arrowLeftXRect.top = 32;
	arrowLeftXRect.width = 32;
	arrowLeftXRect.height = 32;
	arrowRightXRect.left = 544;
	arrowRightXRect.top = 32;
	arrowRightXRect.width = 32;
	arrowRightXRect.height = 32;
	arrowLeftYRect.left = 576;
	arrowLeftYRect.top = 32;
	arrowLeftYRect.width = 32;
	arrowLeftYRect.height = 32;
	arrowRightYRect.left = 640;
	arrowRightYRect.top = 32;
	arrowRightYRect.width = 32;
	arrowRightYRect.height = 32;
	mapSprite.setTexture(*TextureManager::getTexture("map.png"));
	mapSprite.setPosition(416, 0);
	arrowLeftMapRect.left = 384;
	arrowLeftMapRect.top = 32;
	arrowLeftMapRect.width = 32;
	arrowLeftMapRect.height = 32;
	arrowRightMapRect.left = 448;
	arrowRightMapRect.top = 32;
	arrowRightMapRect.width = 32;
	arrowRightMapRect.height = 32;
	teleMapNum = 1;
	tileSelectorRect.left = 672;
	tileSelectorRect.top = 0;
	tileSelectorRect.width = 288;
	tileSelectorRect.height = 768;
	scrollBarSprite.setTexture(*TextureManager::getTexture("scrollbar.png"));
	scrollBarSprite.setPosition(936, 16);
	scrollBarRect.left = scrollBarSprite.getPosition().x;
	scrollBarRect.top = scrollBarSprite.getPosition().y;
	scrollBarRect.width = 16;
	scrollBarRect.height = 32;
	tileSelectSprite.setTexture(*TextureManager::getTexture("tileselect.png"));
	tileSelectSprite.setPosition(224, 32);
	tileSelectRect.left = tileSelectSprite.getPosition().x;
	tileSelectRect.top = tileSelectSprite.getPosition().y;
	tileSelectRect.width = 64;
	tileSelectRect.height = 32;
	tileSelectorOpen = false;
	tileSheetSprite.setTexture(*TextureManager::getTexture("tiles0.png"));
	tileSheetSprite.setPosition(tileSelectorRect.left, tileSelectorRect.top);
	tileSheetRect.left = tileSheetSprite.getPosition().x;
	tileSheetRect.top = tileSheetSprite.getPosition().y;
	tileSheetRect.width = 256;
	tileSheetRect.height = 960;

	for(int i = 0; i <= NUM_MAPS; i++)
	{
		numbers[i].setTexture(*TextureManager::getTexture("numbers.png"));
		numbers[i].setTextureRect(sf::Rect<int>(i * 32, 0, 32, 32));
		numbers[i].setPosition(160, 32);
	}

}

bool Gui::isLoaded()
{

	return loaded;

}

void Gui::tick()
{

	// If the mouse was pressed before but now has been released
	if(mousePressedBefore && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if(mapRect.contains(mousePos) && !tileSelectorOpen)
		{
			// User selected a tile on the map
			// Replace that tile with the one they selected earlier, if they did
			if(tileSelected)
			{
				m.replaceTileType(mousePos.x / 32, (mousePos.y - mapRect.top) / 32, tileTypeSelectedX, tileTypeSelectedY);
				m.updateSprite();
			}
			else if(blockSelected)
			{
				m.flipTileBlocked(mousePos.x / 32, (mousePos.y - mapRect.top) / 32);
				m.updateSprite();
			}
			else if(teleportSelected)
			{
				m.setTileTeleport(mousePos.x / 32, (mousePos.y - mapRect.top) / 32, teleX, teleY, teleMapNum);
				m.updateSprite();
			}
		}
		else if(tileSheetRect.contains(mousePos) && tileSelectorOpen)
		{
			// User selected a tile in the tile sheet
			tileSelected = true;
			blockSelected = false;
			teleportSelected = false;
			tileOutline.setPosition((((mousePos.x - tileSheetRect.left) / 32) * 32) + tileSheetRect.left, (((mousePos.y - tileSheetRect.top) / 32) * 32) + tileSheetRect.top);

			// Determine which tile they selected
			tileTypeSelectedX = (mousePos.x - tileSheetRect.left) / 32;
			tileTypeSelectedY = (mousePos.y - tileSheetRect.top) / 32;
		}
		else if(tileSelectorRect.contains(mousePos) && tileSelectorOpen)
		{
			// See if the scroll bar was moved?
		}
		else if(blockRect.contains(mousePos))
		{
			// User selected the block
			blockSelected = true;
			tileSelected = false;
			teleportSelected = false;
			tileSelectorOpen = false;
			tileOutline.setPosition(blockRect.left, blockRect.top);
		}
		else if(teleportRect.contains(mousePos))
		{
			// User selected the teleport
			teleportSelected = true;
			blockSelected = false;
			tileSelected = false;
			tileSelectorOpen = false;
			tileOutline.setPosition(teleportRect.left, teleportRect.top);
		}
		else if(tileSelectRect.contains(mousePos))
		{
			// User selected the tile selector
			tileSelectorOpen = true;
			teleportSelected = false;
			blockSelected = false;
			tileSelected = true;
			tileOutline.setPosition(tileSelectorRect.left, tileSelectorRect.top);
		}
		else
		{
			//tileSelected = false;
			tileSelectorOpen = false;
			blockSelected = false;
			teleportSelected = false;
		}

		if(arrowLeftRect.contains(mousePos) && (mapNum > 1))
		{
			mapNum--;
			changeMaps();
		}
		else if(arrowRightRect.contains(mousePos) && (mapNum < NUM_MAPS))
		{
			mapNum++;
			changeMaps();
		}
		else if(saveSpriteRect.contains(mousePos))
		{
			m.save();
			cout<<"Saved map.\n";
		}
		else if(arrowLeftMapRect.contains(mousePos) && (teleMapNum > 1) && teleportSelected)
			teleMapNum--;
		else if(arrowRightMapRect.contains(mousePos) && (teleMapNum < 24) && teleportSelected)
			teleMapNum++;
		else if(arrowLeftXRect.contains(mousePos) && (teleX > 0) && teleportSelected)
			teleX--;
		else if(arrowRightXRect.contains(mousePos) && (teleX < 24) && teleportSelected)
			teleX++;
		else if(arrowLeftYRect.contains(mousePos) && (teleY > 0) && teleportSelected)
			teleY--;
		else if(arrowRightYRect.contains(mousePos) && (teleY < 19) && teleportSelected)
			teleY++;
	}

	mousePressedBefore = sf::Mouse::isButtonPressed(sf::Mouse::Left);

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
	mousePos = sf::Mouse::getPosition(*window);

	// Draw stuff
	m.draw(window);
	window->draw(blockSprite);
	window->draw(saveSprite);
	window->draw(teleportSprite);

	// This stuff will move, so move it then draw it
	arrowLeft.setPosition(arrowLeftRect.left, arrowLeftRect.top);
	arrowRight.setPosition(arrowRightRect.left, arrowRightRect.top);
	numbers[mapNum].setPosition(arrowLeftRect.left + 32, arrowLeftRect.top);
	window->draw(arrowLeft);
	window->draw(arrowRight);
	window->draw(numbers[mapNum]);
	window->draw(tileSelectSprite);

	if(blockSelected)
	{
		tileOutline.setPosition(blockRect.left, blockRect.top);
		window->draw(tileOutline);
	}
	else if(teleportSelected)
	{
		tileOutline.setPosition(teleportRect.left, teleportRect.top);
		window->draw(tileOutline);
		window->draw(xSprite);
		window->draw(ySprite);
		window->draw(mapSprite);
		// Move this stuff over and draw it
		arrowLeft.setPosition(arrowLeftXRect.left, arrowLeftXRect.top);
		arrowRight.setPosition(arrowRightXRect.left, arrowRightXRect.top);
		numbers[teleX].setPosition(arrowLeftXRect.left + 32, arrowLeftXRect.top);
		window->draw(arrowLeft);
		window->draw(arrowRight);
		window->draw(numbers[teleX]);
		arrowLeft.setPosition(arrowLeftYRect.left, arrowLeftYRect.top);
		arrowRight.setPosition(arrowRightYRect.left, arrowRightYRect.top);
		numbers[teleY].setPosition(arrowLeftYRect.left + 32, arrowLeftYRect.top);
		window->draw(arrowLeft);
		window->draw(arrowRight);
		window->draw(numbers[teleY]);
		arrowLeft.setPosition(arrowLeftMapRect.left, arrowLeftMapRect.top);
		arrowRight.setPosition(arrowRightMapRect.left, arrowRightMapRect.top);
		numbers[teleMapNum].setPosition(arrowLeftMapRect.left + 32, arrowLeftMapRect.top);
		window->draw(arrowLeft);
		window->draw(arrowRight);
		window->draw(numbers[teleMapNum]);
		tileOutline.setPosition(teleX * 32, mapRect.top + (teleY * 32));
		window->draw(tileOutline);
	}
	else if(tileSelectorOpen)
	{
		window->draw(tileSheetSprite);
		tileOutline.setPosition(tileSelectRect.left, tileSelectRect.top);
		window->draw(tileOutline);
		//window->draw(scrollBarSprite);
		tileOutline.setPosition(tileSheetRect.left + (tileTypeSelectedX * 32), tileSheetRect.top + (tileTypeSelectedY * 32));
		window->draw(tileOutline);
	}

}

Gui::~Gui()
{
}
