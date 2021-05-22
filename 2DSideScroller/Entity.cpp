#include "Entity.h"

Entity::Entity()
{
	hitPoints = 100;

	texture.loadFromFile("spritesheet.png");

	sprite.setTexture(texture);
}

Entity::~Entity()
{
}
