#pragma once
#include <SFML/graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <stack>
#include "GameState.h"


class Game
{
protected:
	//Screen dimensions.
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	//GameState stack
	std::stack<std::shared_ptr<GameState>> states;

public:
	Game(int, int);
	Game();
	~Game();

	//State handler functions.
	void PushState(std::shared_ptr<GameState>);
	void PopState();
	void ChangeState(std::shared_ptr<GameState>);
	std::shared_ptr<GameState> PeekState();
	
	//Main gameloop.
	void GameLoop();

};

