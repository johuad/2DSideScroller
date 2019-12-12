#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Entity.h"

class Player : public Entity
{
protected:
	//player hitpoints
	int hitPoints = 100;
	
	//last facing
	int lastDirection = 1;

	//player initial position
	float initX;
	float initY;

	//player mass
	float mass;

	//player body.
	b2Body * body;

	//player position
	b2Vec2 position;
	//player velocity
	b2Vec2 velocity;

	//player texture
	sf::Texture texture;

	//player sprite
	sf::Sprite sprite;
public:
	Player();
	~Player();

	void setLastDirection(int);
	int getLastDirection();

	// Inherited via Entity
	virtual void setHP() override;
	virtual int getHP() override;

	//movement functions
	virtual void moveY(b2Body *) override;
	virtual void moveX(b2Body *, float) override;

	//create player body
	virtual b2Body *createBody(b2World * world, float, float) override;

	//destroy player/player body. 
	virtual void destroy(b2Body *) override;
	
	//generate and return player sprite.
	virtual sf::Sprite getSprite(b2Body *) override;
};

