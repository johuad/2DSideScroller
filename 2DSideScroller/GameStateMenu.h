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
	Game *game;

	Button *playButton;
	Button *settingsButton;
	Button *exitButton;

	std::vector<Button *> buttons;

	bool clicked = false;
public:
	GameStateMenu(Game *game);
	~GameStateMenu();

	// Inherited via GameState
	virtual void SetupUI(sf::RenderWindow &window) override;
	virtual void Draw(sf::RenderWindow &window, const float delta) override;
	virtual void Update(const float delta) override;
	virtual void HandleInput(sf::RenderWindow &window, sf::Event event) override;
};

