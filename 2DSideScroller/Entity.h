#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Entity
{
protected:
	int hitpoints;

	float mass;

	b2Body * body;

	b2Vec2 position;
	b2Vec2 velocity;
public:
	Entity();
	~Entity();

	virtual void setHP() = 0;
	virtual int getHP() = 0;

	virtual void moveY(b2Body *) = 0;
	virtual void moveX(b2Body *, float) = 0;

	virtual void destroy(b2Body *) = 0;

	virtual b2Body *createBody(b2World *, float, float) = 0;

	virtual sf::Sprite getSprite(b2Body *) = 0;
};

