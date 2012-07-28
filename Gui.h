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
	static const int NUM_MAPS = 25;
	static const enum typeSelected {TS_NONE, TS_BLOCK, TS_TILE, TS_TELE, TS_TILESELECT, TS_PSPAWN, TS_MSPAWN};
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
	sf::Rect<int> tileSelectRect;
	sf::Rect<int> arrowLeftSpriteRect;
	sf::Rect<int> arrowRightSpriteRect;
	sf::Rect<int> arrowLeftLayerRect;
	sf::Rect<int> arrowRightLayerRect;
	sf::Rect<int> pspawnRect;
	sf::Rect<int> mspawnRect;
	sf::Sprite blockSprite;
	sf::Sprite tileOutline;
	sf::Sprite arrowLeft;
	sf::Sprite arrowRight;
	sf::Sprite numbers[26];
	sf::Sprite saveSprite;
	sf::Sprite teleportSprite;
	sf::Sprite xSprite;
	sf::Sprite ySprite;
	sf::Sprite mapSprite;
	sf::Sprite tileSelectSprite;
	sf::Sprite pspawnSprite;
	sf::Sprite mspawnSprite;
	sf::RectangleShape tileBack;
	bool blockSelected;
	bool teleportSelected;
	bool tileSelectorOpen;
	bool pspawnSelected;
	bool mspawnSelected;
	int tileTypeSelectedX;
	int tileTypeSelectedY;
	bool mousePressedBefore;
	int mapNum;
	bool loaded;
	void changeMap();
	void changeTileSheet();
	int teleX;
	int teleY;
	int teleMapNum;
	int tileSheetNum;
	int layerNum;
	//int selected;
public:
	Gui();
	bool isLoaded();
	void tick();
	void draw(sf::RenderWindow *window);
	~Gui();
};

#endif