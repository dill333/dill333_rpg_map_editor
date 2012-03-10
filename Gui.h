#pragma once

#include "Map.h"

// TODO: Implement multiple maps
// TODO: Implement selection for teleporting tiles
// TODO: Handle errors (tile sheet not found)

class Gui
{
	static const int MAP_WIDTH = 800;
	static const int MAP_HEIGHT = 640;
	sf::Sprite tileSheetSprite;
	Map m;
	sf::Rect<int> drawBox;
	bool tileSelected;
	sf::Vector2<int> mousePos;
	sf::Rect<int> mapRect;
	sf::Rect<int> tileSheetRect;
	sf::Rect<int> blockRect;
	sf::Sprite blockSprite;
	sf::Sprite tileOutline;
	bool blockSelected;
	int tileTypeSelectedX;
	int tileTypeSelectedY;
	bool mousePressedBefore;
public:
	Gui();
	void tick();
	void draw(sf::RenderWindow *window);
	~Gui();
};

