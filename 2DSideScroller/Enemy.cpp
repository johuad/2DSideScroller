#include "Enemy.h"

Enemy::Enemy()
{
	hitPoints = 100;

	texture.loadFromFile("spritesheet.png");
	
	sprite.setTexture(texture);
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

void Enemy::moveY(b2Body *body)
{
}

void Enemy::moveX(b2Body *body, float impulse)
{
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
}

void Enemy::destroy(b2Body *body)
{
}

b2Body * Enemy::createBody(b2World *world, float x, float y)
{
	//Create body.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	bodyDef.fixedRotation = true;
	body = world->CreateBody(&bodyDef);

	//Define hitbox.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(5.0f, 20.0f);

	//Define and create Box2D fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.9f;
	fixtureDef.restitution = 0.5f;
	body->CreateFixture(&fixtureDef);

	mass = body->GetMass();

	position = body->GetPosition();
	velocity = body->GetLinearVelocity();

	return body;
}

sf::Sprite Enemy::getSprite(b2Body *body)
{
	sprite.setTextureRect(sf::IntRect(0, 0, 20, 40));
	sprite.setColor(sf::Color::Yellow);
	sprite.setPosition(body->GetPosition().x, body->GetPosition().y);
	sprite.setOrigin(10.f, 20.f);
	return sprite;
}
