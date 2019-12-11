#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <string>

class Tile
{
public:
	Tile();
	~Tile();

	virtual std::string getID() = 0;

	virtual sf::Sprite returnSprite() = 0;
};

