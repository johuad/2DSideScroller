#pragma once
#include "GameState.h"
#include "GameStateMenu.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "ContactListener.h"
#include "Level.h"
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"
#include "Obstacle.h"
#include "Bullet.h"

class GameStatePlay : public GameState
{
private:
	//Pointer back to Game/state handler.
	std::shared_ptr<Game> game;

	//Window view.
	sf::View view;

	//Box2D physics world.
	b2World *world;

	//Used to update the Box2D physics.
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;

	//Contact listener for Box2D
	ContactListener worldContactListener;

	//Vector for storing box2d bodies
	std::vector<b2Body *> bodies;

	//Vector for storing tiles
	std::vector<std::shared_ptr<Tile>> tiles;

	//Flag for firing bullets.
	bool isFiring = false;

	//Current level filename
	std::string curLevel = "";

	//Level
	Level level = Level();

	//Used to generate new level filename
	int levelCount = 0;

	//For next level.
	std::string nextLevel = "";
	std::string lastLevel = "";
	std::ifstream manifest;
	std::string line = "";
	std::vector<std::string> levelManifest;

	//Text
	sf::Text text;
	sf::Font font;

	//Entities
	Player *player;
	Enemy *enemy;
	Obstacle *obstacle;

	//Bodies
	b2Body *playerBody;
	b2Body *enemyBody;
	b2Body *obstacleBody;

public:
	GameStatePlay(std::shared_ptr<Game>, std::string);
	~GameStatePlay();

	//Inherited via GameState
	virtual void Draw(sf::RenderWindow &window, const float delta) override;
	virtual void Update(const float delta) override;
	virtual void HandleInput(sf::RenderWindow &window, sf::Event event) override;

	int GetLevelCount(std::string i);
};

