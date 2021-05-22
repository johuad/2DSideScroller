#pragma once
#include "Entity.h"

class Enemy : public Entity
{
protected:
	int hitPoints;

	float initX;
	float initY;

	float mass;

	b2Body * body;

	b2Vec2 position;
	b2Vec2 velocity;

	sf::Texture texture;

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

