#pragma once
#include "Entity.h"

class Obstacle : public Entity
{
protected:
	//obstacle initial position
	float initX;
	float initY;
	//obstacle mass
	float mass;

	//obtacle body.
	b2Body * body;

	//obstacle position
	b2Vec2 position;
	//obstacle velocity
	b2Vec2 velocity;

	//obstacle texture
	sf::Texture texture;

	//obstacle sprite
	sf::Sprite sprite;
public:
	Obstacle();
	~Obstacle();

	// Inherited via Entity
	virtual void setHP() override;
	virtual int getHP() override;
	virtual void moveY(b2Body *) override;
	virtual void moveX(b2Body *, float) override;
	virtual void destroy(b2Body *) override;
	virtual b2Body * createBody(b2World *, float, float) override;
	virtual sf::Sprite getSprite(b2Body *) override;
};

