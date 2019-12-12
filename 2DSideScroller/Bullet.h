#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Bullet
{
private:
	int speed;
	sf::RectangleShape bullet;
public:
	Bullet(int);
	~Bullet();

	void setPos(sf::Vector2f);

	void fire();

	int getDirection();

	sf::RectangleShape getBullet();
};