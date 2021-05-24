#include "GameStateMenu.h"

GameStateMenu::GameStateMenu(std::shared_ptr<Game> game)
{
	this->game = game;

	//Create menu buttons.
	playButton = std::shared_ptr<Button>(new Button());
	exitButton = std::shared_ptr<Button>(new Button());

	//Push menu buttons onto the list.
	buttons.push_back(playButton);
	buttons.push_back(exitButton);
}

GameStateMenu::~GameStateMenu()
{
}


void GameStateMenu::Draw(sf::RenderWindow &window, const float delta)
{
	sf::View view = window.getDefaultView();

	//Set the view to the default for the renderwindow.
	window.setView(view);
	//Clear for each frame.
	window.clear(sf::Color::White);

	//Set button parameters.
	playButton->GenerateButton("play", (float) window.getSize().x / 2, (float) window.getSize().y / 2 + 55.0, 100.0, 50.0);
	exitButton->GenerateButton("exit", (float) window.getSize().x / 2, (float) window.getSize().y / 2 + 110.0, 100.0, 50.0);

	//Draw the buttons.
	for (auto &b : buttons) 
	{
		if (!buttons.size() == 0)
		{
			window.draw(b->GetButton());
			window.draw(b->GetText());
		}
	}
}

void GameStateMenu::Update(const float delta)
{

}

void GameStateMenu::HandleInput(sf::RenderWindow &window, sf::Event event)
{
	//Pixel & world positions for mouse input.
	sf::Vector2i pixelPos;
	sf::Vector2f worldPos;

	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (!clicked)
				{
					pixelPos = sf::Mouse::getPosition(window);
					worldPos = window.mapPixelToCoords(pixelPos);
					for (auto &b : buttons)
					{
						if (b->GetButton().getGlobalBounds().contains(worldPos))
						{
							if (b->GetButtonID() == "play")
							{
								game->ChangeState(std::shared_ptr<GameStatePlay>(new GameStatePlay(game, "level1.txt")));
							}
							if (b->GetButtonID() == "exit")
							{
								std::exit(0);
							}
						}
					}
					clicked = true;
				}
			}
			break;

		case sf::Event::MouseButtonReleased:
			clicked = false;
			break;

		default:
			break;
	}
}
