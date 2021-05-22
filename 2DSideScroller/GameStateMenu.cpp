#include "GameStateMenu.h"

GameStateMenu::GameStateMenu(std::shared_ptr<Game> game)
{
	this->game = game;

	playButton = std::shared_ptr<Button>(new Button());
	exitButton = std::shared_ptr<Button>(new Button());

	buttons.push_back(playButton);
	buttons.push_back(exitButton);
}

GameStateMenu::~GameStateMenu()
{
}


void GameStateMenu::Draw(sf::RenderWindow &window, const float delta)
{
	sf::View view = window.getDefaultView();

	window.setView(view);

	window.clear(sf::Color::White);

	playButton->GenerateButton("play", window.getSize().x / 2, window.getSize().y / 2 + 55, 100, 50);
	exitButton->GenerateButton("exit", window.getSize().x / 2, window.getSize().y / 2 + 110, 100, 50);

	for (auto &b : buttons) 
	{
		if (!buttons.size() == 0)
		{
			window.draw(b->GetButton());
		}
	}
}

void GameStateMenu::Update(const float delta)
{

}

void GameStateMenu::HandleInput(sf::RenderWindow &window, sf::Event event)
{
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
