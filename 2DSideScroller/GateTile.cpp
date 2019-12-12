#include "GateTile.h"

GateTile::GateTile(float r, float c, int x, int y, int sx, int sy)
{
	texture.loadFromFile("spritesheet.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(x, y, sx, sy));
	sprite.setPosition(r, c);
	sprite.setOrigin(25, 25);
}

GateTile::~GateTile()
{
}

b2Body * GateTile::returnBody()
{
	return nullptr;
}

std::string GateTile::getID()
{
	return id;
}

sf::Sprite GateTile::returnSprite()
{
	return sprite;
}
