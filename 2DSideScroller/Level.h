#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <string>
#include <fstream>
#include <iostream>

class Level
{
private:
	//initial player position
	float initX;
	float initY;

	int **level;

	//storage for level.
	std::vector<sf::RectangleShape> tiles;
public:
	Level();
	~Level();

	void generateLevel(b2World *, std::vector<sf::RectangleShape> *, std::string, int, int);

	float getInitX();
	float getInitY();
};

