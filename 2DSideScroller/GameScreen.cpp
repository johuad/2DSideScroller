#include "GameScreen.h"

GameScreen::GameScreen()
{
	//set up window & window title.
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "2DSideScroller");
	//limit framerate
	window.setFramerateLimit(60);

	//set up & initialize a view.
	sf::View view = window.getDefaultView();

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//initialize menu, will auto display
		menu = new Menu(window);

		window.clear(sf::Color::White);
		//display everything
		window.display();
	}
}

GameScreen::~GameScreen()
{
}
