#include "Game.h"

Game::Game(int w, int h)
{
	//Set up screen dimensions.
	SCREEN_WIDTH = w;
	SCREEN_HEIGHT = h;

}

Game::Game()
{
}

Game::~Game()
{

}

void Game::PushState(std::shared_ptr<GameState> state)
{
	//Push a new state on top of the stack.
	states.push(state);
	std::cout << states.size() << std::endl;
}

void Game::PopState()
{
	//Delete the state on the top of the stack.
	//delete &states.top();
	
	//pop it.
	states.pop();

	std::cout << states.size() << std::endl;
	return;
}

void Game::ChangeState(std::shared_ptr<GameState> state)
{
	if (!states.empty())
	{
		PopState();
	}
	PushState(state);

	std::cout << states.size() << std::endl;
}

std::shared_ptr<GameState> Game::PeekState()
{
	//Look at the top of the stack.
	if (states.empty()) 
	{
		return nullptr;
	}
	else 
	{
		return states.top();
	}
}

void Game::GameLoop()
{
	//Set up a clock for calculating delta time.
	sf::Clock clock;

	//Create render window & set title.
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "2D Side Scroller");

	//Limit framerate to 60.
	window.setFramerateLimit(60);

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
