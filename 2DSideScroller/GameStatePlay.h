#pragma once
#include "GameState.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include <iostream>
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
	//Pointer to our state handler.
	Game *game;

	//Box2D physics world.
	b2World *world;

	//Used to update the Box2D physics.
	int32 velocityIterations;
	int32 positionIterations;

	//Contact listener for Box2D
	ContactListener worldContactListener;

	//Vector for storing box2d bodies
	std::vector<b2Body *> bodies;

	//Vector for storing tiles
	std::vector<Tile*> tiles;

	//Flag for firing bullets.
	bool isFiring;

	//Current level filename
	std::string curLevel;

	//Level
	Level level = Level();

	//Used to generate new level filename
	int levelCount;

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
	GameStatePlay(Game *game, std::string levelName);
	~GameStatePlay();

	//Inherited via GameState
	virtual void SetupUI(sf::RenderWindow & window) override;
	virtual void Draw(sf::RenderWindow & window, const float delta) override;
	virtual void Update(const float delta) override;
	virtual void HandleInput(sf::RenderWindow & window, sf::Event event) override;

	int GetLevelCount(std::string i);
};

