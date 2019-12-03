#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

class Level
{
private:
	//initial player position
	float initX;
	float initY;

	int *level[10][40];

	//storage for level.
	std::vector<sf::RectangleShape> tiles;
public:
	Level();
	~Level();

	void generateLevel(b2World *, std::vector<sf::RectangleShape> *);

	float getInitX();
	float getInitY();
};

