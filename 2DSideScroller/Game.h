#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include "ContactListener.h"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Obstacle.h"
#include "Tile.h"

class Game
{
private:
	//contact listener
	ContactListener worldContactListener;

	//vector for storing box2d bodies
	std::vector<b2Body *> bodies;

	//vector for storing tiles
	std::vector<Tile*> tiles;

	//current level filename
	std::string curLevel;

	//level
	Level level = Level();

	//used to generate new level filename
	int levelCount;

	//text
	sf::Text text;

	//font
	sf::Font font;

	//player object
	Player player = Player();
	//uninitialized body for player
	b2Body *playerBody;

	//enemy object
	Enemy enemy = Enemy();
	//uninitialized body for enemy
	b2Body *enemyBody;

	//obstacle object
	Obstacle obstacle = Obstacle();
	//uninitialized body for obstacle
	b2Body *obstacleBody;
public:
	Game(sf::RenderWindow &, std::string);
	~Game();

	//get number in current level filename
	int getLevelCount(std::string);
};

