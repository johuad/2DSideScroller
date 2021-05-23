#pragma once
#include "GameState.h"
#include "GameStatePlay.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include <string>
#include "Button.h"

class GameStateMenu : public GameState
{
private:
	//Pointer back to Game/state handler.
	std::shared_ptr<Game> game;

	std::shared_ptr<Button> playButton;
	std::shared_ptr<Button> exitButton;

	std::vector<std::shared_ptr<Button>> buttons;

	bool clicked = false;
public:
	GameStateMenu(std::shared_ptr<Game>);
	~GameStateMenu();

	// Inherited via GameState
	virtual void Draw(sf::RenderWindow &, const float) override;
	virtual void Update(const float) override;
	virtual void HandleInput(sf::RenderWindow &, sf::Event) override;
};

