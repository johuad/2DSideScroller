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
	float initX = 0.0;
	float initY = 0.0;

	//Initial enemy position.
	float initXE = 0.0;
	float initYE = 0.0;

	//Initial obstacle position.
	float initXO = 0.0;
	float initYO = 0.0;

	//Blank 2D array for level generation.
	int **level;

	//Vector to store tiles as they're created.
	std::vector<sf::RectangleShape> tiles;
	
	//Blank tile declaration.
	std::shared_ptr<Tile> tile;

public:
	Level(b2World *world, std::vector<std::shared_ptr<Tile>> *tiles, std::string fileName, int row, int col);
	Level();
	~Level();

	//Box2D body for creating static tiles the player can collide with.
	b2Body * body;

	//Fetters for initial positions (spawn points)
	float getInitX();
	float getInitY();
	float getInitXE();
	float getInitYE();
	float getInitXO();
	float getInitYO();

};

