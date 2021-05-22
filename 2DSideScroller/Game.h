#pragma once
#include <SFML/graphics.hpp>
#include <SFML/System.hpp>
#include <stack>
#include <iostream>
#include "GameState.h"


class Game
{
protected:
	//Screen dimensions.
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	//GameState stack
	std::stack<GameState *> states;

public:
	Game(int, int);
	~Game();

	void PushState(GameState *state);

	void PopState();

	GameState * PeekState();

	void GameLoop();
};

