#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Bullet
{
private:
	//Bullet speed.
	int speed;

	//Bullet is a simple SFML rectangle.
	sf::RectangleShape bullet;

public:
	Bullet(int s);
	~Bullet();

	//Setter for bullet position on screen.
	void setPos(sf::Vector2f pos);

	//Function for firing a bullet.
	void fire();

	//Getter for bullet direction.
	int getDirection();

	//Getter for bullet.
	sf::RectangleShape getBullet();
};