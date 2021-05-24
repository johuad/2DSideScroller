#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include "Entity.h"
#include "Bullet.h"

class Player : public Entity
{
protected:
	int hitPoints = 100;
	
	float initX = 0.0;
	float initY = 0.0;
	float mass = 0.0;

	//Last facing.
	int lastDirection = 1;

	//Movement flags.
	bool moveLeft = false;
	bool moveRight = false;

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

	virtual b2Body * createBody(b2World *world, float x, float y) override;
	virtual void destroy(b2Body *body) override;

	virtual sf::Sprite getSprite(b2Body *body) override;

	virtual void moveY(b2Body *body) override;
	virtual void moveX(b2Body *body, float impulse) override;

	void setLastDirection(int i);
	int getLastDirection();

	void FireBullet();
};

