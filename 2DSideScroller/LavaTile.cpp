#include "LavaTile.h"

LavaTile::LavaTile(float r, float c, int x, int y, int sx, int sy)
{
	texture.loadFromFile("spritesheet.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(x, y, sx, sy));
	sprite.setPosition(r, c);
	sprite.setOrigin(25, 25);
}

LavaTile::~LavaTile()
{
}

std::string LavaTile::getID()
{
	return id;
}

sf::Sprite LavaTile::returnSprite()
{
	return sprite;
}
