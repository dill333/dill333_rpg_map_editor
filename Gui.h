#pragma once

#include "Map.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// TODO: Implement selection for teleporting tiles
// TODO: Handle errors (tile sheet not found)
// TODO: Get rid of the ugly block of initialization code

class Gui
{
	static const int MAP_WIDTH = 800;
	static const int MAP_HEIGHT = 640;
	static const int NUM_MAPS = 24;
	sf::Sprite tileSheetSprite;
	Map m;
	sf::Rect<int> drawBox;
	bool tileSelected;
	sf::Vector2<int> mousePos;
	sf::Rect<int> mapRect;
	sf::Rect<int> tileSheetRect;
	sf::Rect<int> blockRect;
	sf::Rect<int> arrowLeftRect;
	sf::Rect<int> arrowRightRect;
	sf::Rect<int> saveSpriteRect;
	sf::Rect<int> teleportRect;
	sf::Rect<int> arrowLeftXRect;
	sf::Rect<int> arrowRightXRect;
	sf::Rect<int> arrowLeftYRect;
	sf::Rect<int> arrowRightYRect;
	sf::Sprite blockSprite;
	sf::Sprite tileOutline;
	sf::Sprite arrowLeft;
	sf::Sprite arrowRight;
	sf::Sprite numbers[NUM_MAPS + 1];
	sf::Sprite saveSprite;
	sf::Sprite teleportSprite;
	sf::Sprite xSprite;
	sf::Sprite ySprite;
	bool blockSelected;
	bool teleportSelected;
	int tileTypeSelectedX;
	int tileTypeSelectedY;
	bool mousePressedBefore;
	int mapNum;
	bool loaded;
	void changeMaps();
	int teleX;
	int teleY;
public:
	Gui();
	bool isLoaded();
	void tick();
	void draw(sf::RenderWindow *window);
	~Gui();
};

