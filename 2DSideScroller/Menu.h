#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Game.h"

class Menu
{
private:
	sf::Text text;
	sf::Font font;
public:
	Menu(sf::RenderWindow &);
	~Menu();

	//game levels
	Game *level1;
	Game *level2;
	Game *level3;
};

