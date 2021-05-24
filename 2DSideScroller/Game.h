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
	unsigned int SCREEN_WIDTH = 0;
	unsigned int SCREEN_HEIGHT = 0;

	//GameState stack.
	std::stack<std::shared_ptr<GameState>> states;

public:
	Game(unsigned int w, unsigned int h);
	Game();
	~Game();

	//State handler functions.
	void PushState(std::shared_ptr<GameState>);
	void PopState();
	void ChangeState(std::shared_ptr<GameState>);
	std::shared_ptr<GameState> PeekState();
	
	//Run the main gameloop.
	void GameLoop();

};

