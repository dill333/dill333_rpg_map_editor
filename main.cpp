#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Map.h"

using namespace std;

// TODO: Overload the operator << and >> for map
// Should save all of the tiles, which are already overloaded
// Should probably do entities and whatnot later

static const int GAME_WIDTH = 800;
static const int GAME_HEIGHT = 640;
static const int WINDOW_WIDTH = 960;
static const int WINDOW_HEIGHT = 768;
static const int FPS = 30;

int main()
{

	/*ofstream myfile;

	Tile t;

	myfile.open("example.txt");
	myfile<<t;
	myfile.close();

	ifstream ifile;

	ifile.open("example.txt");
	ifile>>t;
	ifile.close();

	cout<<t;*/

	// Our render window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "RPG Map Editor");

	// Limit the framerate
	window.SetFramerateLimit(FPS);

	// The map
	Map m;

	if(!m.getLoaded())
		return 1;

	// The main loop
	while(window.IsOpened())
	{
		sf::Event event;
		while(window.PollEvent(event))
		{
			// Request for closing the window
			if(event.Type == sf::Event::Closed)
				window.Close();
		}

		// Clear the window
		window.Clear();

		// Draw the map
		m.draw(window);

		// Display the contents on the screen
		window.Display();
	}

	m.save();

	return 0;

}