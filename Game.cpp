#include "Game.h"

Game::Game()
{

	// Our render window
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "RPG Map Editor");
	window.setFramerateLimit(FPS);
	loaded = gui.isLoaded();

}

void Game::run()
{

	// The main loop, make sure everything initialized OK
	if(loaded)
	{
		while(window.isOpen())
		{
			sf::Event event;
			while(window.pollEvent(event))
			{
				// Request for closing the window
				if(event.type == sf::Event::Closed)
					window.close();
			}

			// Clear the window
			window.clear(sf::Color::White);

			// Tick everything that needs it
			gui.tick();

			// Draw everything
			gui.draw(&window);

			// Display the window
			window.display();
		}
	}
	else
	{
		cout<<"Error in initialization!  Press enter to quit.\n";
		cin.get();
	}

}

Game::~Game()
{
}
