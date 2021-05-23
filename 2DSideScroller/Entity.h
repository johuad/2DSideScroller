#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Entity
{
protected:
	//Entity hitpoints.
	int hitPoints;

	//Entity mass.
	float mass;

	//Entity Box2D body.
	std::shared_ptr<b2Body> body;

	//Entity position.
	b2Vec2 position;

	//Entity velocity.
	b2Vec2 velocity;

	//Entity texture.
	sf::Texture texture;

	//Entity Sprite.
	sf::Sprite sprite;

public:
	Entity();
	~Entity();

	//Setter & Getter for Entity hitpoints.
	virtual void setHP() = 0;
	virtual int getHP() = 0;

	//Movement functions.
	virtual void moveY(b2Body *) = 0;
	virtual void moveX(b2Body *, float) = 0;

	//Destroy Entity's Box2D Body.
	virtual void destroy(b2Body *) = 0;

	//Create Entity's Box2D body.
	virtual b2Body * createBody(b2World *, float, float) = 0;

	//Create and return sprite.
	virtual sf::Sprite getSprite(b2Body *) = 0;
};

