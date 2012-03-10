#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Gui.h"

using namespace std;

class Game
{
	sf::RenderWindow window;
	Gui gui;
	bool loaded;
public:
	static const int WINDOW_WIDTH = 960;
	static const int WINDOW_HEIGHT = 768;
	static const int FPS = 30;
	Game();
	void run();
	~Game();
};