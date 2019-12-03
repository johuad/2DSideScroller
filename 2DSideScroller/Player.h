#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Player
{
private:
	//player body.
	b2Body * body;

	//player hitpoints
	int hitPoints = 100;

	//player mass
	float mass;

	//player position
	b2Vec2 position;
	
	//player velocity
	b2Vec2 velocity;
public:
	Player();
	~Player();

	//create player body
	b2Body *createBody(b2World * world, float, float);

	//return player HP
	int getHitPoints();

	//movement functions
	void moveUp(b2Body *);
	void moveX(b2Body *, float);

	//player takes damage
	void takeDamage();

	//player dies
	void death(b2Body *);

	//draw player
	sf::RectangleShape drawable(b2Body *);
};

