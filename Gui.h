#ifndef GUI_H
#define GUI_H

#include "Map.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

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
	sf::Rect<int> arrowLeftMapRect;
	sf::Rect<int> arrowRightMapRect;
	sf::Rect<int> tileSelectorRect;
	sf::Rect<int> tileSelectRect;
	sf::Rect<int> scrollBarRect;
	sf::Sprite blockSprite;
	sf::Sprite tileOutline;
	sf::Sprite arrowLeft;
	sf::Sprite arrowRight;
	sf::Sprite numbers[NUM_MAPS + 1];
	sf::Sprite saveSprite;
	sf::Sprite teleportSprite;
	sf::Sprite xSprite;
	sf::Sprite ySprite;
	sf::Sprite mapSprite;
	sf::Sprite scrollBarSprite;
	sf::Sprite tileSelectSprite;
	bool blockSelected;
	bool teleportSelected;
	bool tileSelectorOpen;
	int tileTypeSelectedX;
	int tileTypeSelectedY;
	bool mousePressedBefore;
	int mapNum;
	bool loaded;
	void changeMaps();
	int teleX;
	int teleY;
	int teleMapNum;
public:
	Gui();
	bool isLoaded();
	void tick();
	void draw(sf::RenderWindow *window);
	~Gui();
};

#endif