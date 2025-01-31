#include "Bullet.h"

Bullet::Bullet(int s)
{
	//Set speed to s.
	speed = s;

	//Set Bullet size & color.
	bullet.setSize(sf::Vector2f(4, 4));
	bullet.setFillColor(sf::Color::Green);
}

Bullet::~Bullet()
{
}

void Bullet::setPos(sf::Vector2f pos)
{
	bullet.setPosition(pos);
}

void Bullet::fire()
{
	bullet.move(speed, 0.0);
}

int Bullet::getDirection()
{
	return speed;
}

sf::RectangleShape Bullet::getBullet()
{
	return bullet;
}

