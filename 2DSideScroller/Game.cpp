#include "Game.h"

Game::Game(int w, int h)
{
	//Set up screen dimensions.
	SCREEN_WIDTH = w;
	SCREEN_HEIGHT = h;

}

Game::~Game()
{
}

void Game::PushState(GameState * state)
{
	//Push a new state on top of the stack.
	this->states.push(state);
}

void Game::PopState()
{
	//Delete the state on the top of the stack.
	delete this->states.top();
	
	//pop it.
	states.pop();
	
	return;
}

GameState * Game::PeekState()
{
	//Look at the top of the stack.
	if (this->states.empty()) 
	{
		return nullptr;
	}
	else 
	{
		return this->states.top();
	}
}

void Game::GameLoop()
{
	//Set up a clock for calculating delta time.
	sf::Clock clock;

	//Create render window & set title.
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "2D Side Scroller");

	//Set up & initialize view.
	sf::View view = window.getDefaultView();

	//Limit framerate to 60.
	window.setFramerateLimit(60);

	//Set up state's UI if one exists.
	PeekState()->SetupUI(window);

	while (window.isOpen())
	{
		sf::Event event;

		//Initialize delta time.
		sf::Time elapsed = clock.restart();
		float delta = elapsed.asSeconds();

		while (window.pollEvent(event))
		{
			//Allow the window to close.
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (PeekState() == nullptr) 
		{
			continue;
		}
		else
		{
			PeekState()->HandleInput(window, event);
			PeekState()->Update(delta);
			PeekState()->Draw(window, delta);
		}
		
		window.display();

	}
}
