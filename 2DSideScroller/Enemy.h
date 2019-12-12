#pragma once
#include "Entity.h"

class Enemy : public Entity
{
protected:
	//enemy hitpoints
	int hitPoints;

	//enemy initial position
	float initX;
	float initY;
	//enemy mass
	float mass;

	//enemy body.
	b2Body * body;

	//enemy position
	b2Vec2 position;
	//enemy velocity
	b2Vec2 velocity;

	//enemy texture
	sf::Texture texture;

	//enemy sprite
	sf::Sprite sprite;
public:
	Enemy();
	~Enemy();

	// Inherited via Entity
	virtual void setHP() override;
	virtual int getHP() override;
	virtual void moveY(b2Body *) override;
	virtual void moveX(b2Body *, float) override;
	virtual void destroy(b2Body *) override;
	virtual b2Body * createBody(b2World *, float, float) override;
	virtual sf::Sprite getSprite(b2Body *) override;
};

