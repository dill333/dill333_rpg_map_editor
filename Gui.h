#pragma once

#include "Map.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// TODO: Implement selection for teleporting tiles
// TODO: Handle errors (tile sheet not found)

class Gui
{
	static const int MAP_WIDTH = 800;
	static const int MAP_HEIGHT = 640;
	static const int NUM_MAPS = 10;
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
	sf::Sprite blockSprite;
	sf::Sprite tileOutline;
	sf::Sprite arrowLeft;
	sf::Sprite arrowRight;
	sf::Sprite numbers[NUM_MAPS];
	sf::Sprite saveSprite;
	bool blockSelected;
	int tileTypeSelectedX;
	int tileTypeSelectedY;
	bool mousePressedBefore;
	int mapNum;
	bool loaded;
	void changeMaps();
public:
	Gui();
	bool isLoaded();
	void tick();
	void draw(sf::RenderWindow *window);
	~Gui();
};

