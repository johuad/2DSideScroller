#include "Enemy.h"

Enemy::Enemy()
{
	texture.loadFromFile("spritesheet.png");
	sprite.setTexture(texture);
	hitPoints = 100;
}

Enemy::~Enemy()
{
}

void Enemy::setHP()
{
	hitPoints = hitPoints - 25;
}

int Enemy::getHP()
{
	return hitPoints;
}

void Enemy::moveY(b2Body *)
{
}

void Enemy::moveX(b2Body *body, float impulse)
{
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
}

void Enemy::destroy(b2Body *)
{
}

b2Body * Enemy::createBody(b2World * world, float x, float y)
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
	dynamicBox.SetAsBox(10.0f, 20.0f);

	b2FixtureDef fixtureDef;
	//apply hitbox to fixture
	fixtureDef.shape = &dynamicBox;
	//set density of our fixture
	fixtureDef.density = 1.0f;
	//set friction of our fixture
	fixtureDef.friction = 0.9f;
	//set fixture restitution
	fixtureDef.restitution = 0.5f;
	//apply fixture to body
	body->CreateFixture(&fixtureDef);

	mass = body->GetMass();

	position = body->GetPosition();
	velocity = body->GetLinearVelocity();

	return body;
}

sf::Sprite Enemy::getSprite(b2Body *)
{
	sprite.setTextureRect(sf::IntRect(50, 0, 20, 40));
	sprite.setColor(sf::Color::Yellow);
	sprite.setPosition(body->GetPosition().x, body->GetPosition().y);
	sprite.setOrigin(10.f, 20.f);
	return sprite;
}
