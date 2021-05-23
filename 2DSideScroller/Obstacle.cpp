#include "Obstacle.h"

Obstacle::Obstacle()
{
	texture.loadFromFile("spritesheet.png");
	sprite.setTexture(texture);
}

Obstacle::~Obstacle()
{
}

void Obstacle::setHP()
{
}

int Obstacle::getHP()
{
	return 0;
}

void Obstacle::moveY(b2Body *)
{
}

void Obstacle::moveX(b2Body *, float)
{
}

void Obstacle::destroy(b2Body *)
{
}

b2Body * Obstacle::createBody(b2World * world, float x, float y)
{
	//Create body.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.fixedRotation = true;
	body = world->CreateBody(&bodyDef);

	//Define hitbox.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(10.0f, 25.0f);

	//Define and create Box2D fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 5.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 0.0f;
	body->CreateFixture(&fixtureDef);

	mass = body->GetMass();

	position = body->GetPosition();
	velocity = body->GetLinearVelocity();

	return body;
}

sf::Sprite Obstacle::getSprite(b2Body *)
{
	sprite.setTextureRect(sf::IntRect(0, 110, 20, 50));
	sprite.setPosition(body->GetPosition().x, body->GetPosition().y);
	sprite.setOrigin(10.f, 25.f);

	return sprite;
}
