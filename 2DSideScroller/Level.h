#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <string>
#include <fstream>
#include "Tile.h"
#include "GroundTile.h"
#include "LavaTile.h"
#include "GateTile.h"
#include "GoalTile.h"

class Level
{
private:
	//Initial player position.
	float initX;
	float initY;

	//Initial enemy position.
	float initXE;
	float initYE;

	//Initial obstacle position.
	float initXO;
	float initYO;

	//Blank 2D array for level generation.
	int **level;

	//Vector to store tiles as they're created.
	std::vector<sf::RectangleShape> tiles;
	
	//Blank tile declaration.
	Tile * tile;
public:
	Level();
	~Level();

	b2Body * body;

	//function to generate level
	void generateLevel(b2World *, std::vector<Tile*> *, std::string, int, int);

	//getters for initial positions (spawn points)
	float getInitX();
	float getInitY();
	float getInitXE();
	float getInitYE();
	float getInitXO();
	float getInitYO();
};

