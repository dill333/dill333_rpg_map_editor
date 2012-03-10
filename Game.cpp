#include "Game.h"

Game::Game()
{

	// Our render window
	window.Create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "RPG Map Editor");
	window.SetFramerateLimit(FPS);
	loaded = m.isLoaded();

}

void Game::run()
{

	// The main loop, make sure everything initialized OK
	if(loaded)
	{
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
			window.Clear(sf::Color::White);

			// Tick everything that needs it
			gui.tick();

			// Draw everything
			gui.draw(&window);

			// Display the window
			window.Display();
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
