#include "GoalTile.h"

GoalTile::GoalTile(float r, float c, int x, int y, int sx, int sy)
{
	texture.loadFromFile("spritesheet.png");
	sprite.setTexture(texture);
	sprite.setColor(sf::Color::Green);
	sprite.setTextureRect(sf::IntRect(x, y, sx, sy));
	sprite.setPosition(r, c);
	sprite.setOrigin(25, 25);
}

GoalTile::~GoalTile()
{
}

b2Body * GoalTile::returnBody()
{
	return nullptr;
}

std::string GoalTile::getID()
{
	return id;
}

sf::Sprite GoalTile::returnSprite()
{
	return sprite;
}
