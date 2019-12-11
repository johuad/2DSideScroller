#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <string>
#include <fstream>
#include <iostream>
#include "Tile.h"
#include "GroundTile.h"
#include "LavaTile.h"
#include "GoalTile.h"

class Level
{
private:
	//initial player position
	float initX;
	float initY;

	//pointer to 2d array
	int **level;

	//storage for level.
	std::vector<sf::RectangleShape> tiles;
public:
	Level();
	~Level();

	b2Body * body;

	//function to generate level
	void generateLevel(b2World *, std::vector<Tile*> *, std::string, int, int);

	//getters for initial position (spawn point)
	float getInitX();
	float getInitY();
};

