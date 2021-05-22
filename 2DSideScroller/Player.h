#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include "Entity.h"
#include "Bullet.h"

class Player : public Entity
{
protected:
	//Player hitpoints.
	int hitPoints;
	
	//Last facing.
	int lastDirection;

	//Initial player position.
	float initX;
	float initY;

	//Player mass.
	float mass;

	//Movement flags.
	bool moveLeft;
	bool moveRight;

	//Player Box2D body.
	b2Body * body;

	//Player position.
	b2Vec2 position;
	
	//Player velocity.
	b2Vec2 velocity;

	//Player sprite texture.
	sf::Texture texture;

	//Player sprite.
	sf::Sprite sprite;

public:
	Player();
	~Player();

	//Bullets.
	std::vector<Bullet> bullets;
	
	void setLastDirection(int);

	int getLastDirection();

	void FireBullet();

	//Setter & Getter for player hitpoints.
	virtual void setHP() override;

	virtual int getHP() override;

	//Player movement.
	virtual void moveY(b2Body *) override;

	virtual void moveX(b2Body *, float) override;

	//Create player's Box2D body.
	virtual b2Body *createBody(b2World *, float, float) override;

	//Destroy player's Box2D body.
	virtual void destroy(b2Body *) override;
	
	//Create the player sprite.
	virtual sf::Sprite getSprite(b2Body *) override;
};

