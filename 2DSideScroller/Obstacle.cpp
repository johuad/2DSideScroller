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
	b2BodyDef bodyDef;
	//set body type
	bodyDef.type = b2_dynamicBody;
	//set body position
	bodyDef.position.Set(x, y);
	//prevent body from rotating
	bodyDef.fixedRotation = true;
	//create body
	body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	//define hitbox dimensions
	dynamicBox.SetAsBox(10.0f, 25.0f);

	b2FixtureDef fixtureDef;
	//apply hitbox to fixture
	fixtureDef.shape = &dynamicBox;
	//set density of our fixture
	fixtureDef.density = 5.0f;
	//set friction of our fixture
	fixtureDef.friction = 0.0f;
	//set fixture restitution
	fixtureDef.restitution = 0.0f;
	//apply fixture to body
	body->CreateFixture(&fixtureDef);

	mass = body->GetMass();

	position = body->GetPosition();
	velocity = body->GetLinearVelocity();

	return body;
}

sf::Sprite Obstacle::getSprite(b2Body *)
{
	sprite.setTextureRect(sf::IntRect(0, 50, 20, 50));
	sprite.setColor(sf::Color::Magenta);
	sprite.setPosition(body->GetPosition().x, body->GetPosition().y);
	sprite.setOrigin(10.f, 25.f);

	return sprite;
}
