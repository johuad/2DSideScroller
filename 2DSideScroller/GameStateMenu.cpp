#include "GameStateMenu.h"

GameStateMenu::GameStateMenu(Game *game)
{
	this->game = game;

	playButton = new Button();
	settingsButton = new Button();
	exitButton = new Button();

}

GameStateMenu::~GameStateMenu()
{
}

void GameStateMenu::SetupUI(sf::RenderWindow &window)
{
	playButton->GenerateButton("play", window.getSize().x / 2, window.getSize().y / 2 + 55, 100, 50);
	buttons.push_back(playButton);

	settingsButton->GenerateButton("settings", window.getSize().x / 2, window.getSize().y / 2 + 110, 100, 50);
	buttons.push_back(settingsButton);

	exitButton->GenerateButton("exit", window.getSize().x / 2, window.getSize().y / 2 + 165, 100, 50);
	buttons.push_back(exitButton);
}

void GameStateMenu::Draw(sf::RenderWindow &window, const float delta)
{
	window.clear(sf::Color::White);

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
								game->PushState(new GameStatePlay(game, "level1.txt"));
							}
							if (b->GetButtonID() == "settings")
							{
								std::cout << "settings clicked" << std::endl;
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
