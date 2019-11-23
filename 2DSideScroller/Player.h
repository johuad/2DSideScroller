#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Player
{
private:
	b2Body *body;
	float mass;

	b2Vec2 position;
	b2Vec2 velocity;
public:
	Player();
	~Player();

	b2Body *createBody(b2World *world, float, float);

	void moveUp(b2Body *);
	void moveX(b2Body *, float);

	sf::RectangleShape drawable(b2Body *);
};

