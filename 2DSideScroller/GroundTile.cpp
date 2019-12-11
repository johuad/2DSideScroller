#include "GroundTile.h"

GroundTile::GroundTile(b2World * w, float r, float c, int x, int y, int sx, int sy)
{
	world = w;

	b2BodyDef bodyDef;

	bodyDef.position.Set(r, c);

	body = world->CreateBody(&bodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(25.0f, 25.0f);

	b2FixtureDef fixtureDef;

	fixtureDef.shape = &groundBox;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 0.f;

	body->CreateFixture(&fixtureDef);

	b2Vec2 groundPos = body->GetPosition();

	texture.loadFromFile("spritesheet.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(x, y, sx, sy));
	sprite.setPosition(groundPos.x, groundPos.y);
	sprite.setOrigin(25, 25);
}

GroundTile::~GroundTile()
{
	world->DestroyBody(body);
}

std::string GroundTile::getID()
{
	return id;
}

b2Body * GroundTile::returnBody()
{
	return body;
}

sf::Sprite GroundTile::returnSprite()
{
	return sprite;
}