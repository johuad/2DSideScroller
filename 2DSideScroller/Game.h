#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "ContactListener.h"
#include "Level.h"
#include "Player.h"
#include "Tile.h"

class Game
{
public:
	Game(sf::RenderWindow &, std::string);
	~Game();
};

