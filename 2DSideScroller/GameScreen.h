#pragma once
#include <SFML/graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include "Menu.h"
#include "Game.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class GameScreen
{
private:
	//set up menu
	Menu *menu;
public:
	GameScreen();
	~GameScreen();
};

