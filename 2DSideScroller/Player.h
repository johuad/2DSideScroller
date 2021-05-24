#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include "Entity.h"
#include "Bullet.h"

class Player : public Entity
{
protected:
	int hitPoints;
	
	float initX;
	float initY;
	float mass;

	//Last facing.
	int lastDirection;

	//Movement flags.
	bool moveLeft;
	bool moveRight;

	b2Body * body;

	b2Vec2 position;
	b2Vec2 velocity;

	sf::Texture texture;

	sf::Sprite sprite;

public:
	Player();
	~Player();
	
	std::vector<Bullet> bullets;

	virtual void setHP() override;
	virtual int getHP() override;

	virtual b2Body * createBody(b2World *, float, float) override;
	virtual void destroy(b2Body *) override;

	virtual sf::Sprite getSprite(b2Body *) override;

	virtual void moveY(b2Body *) override;
	virtual void moveX(b2Body *, float) override;

	void setLastDirection(int);
	int getLastDirection();

	void FireBullet();
};

