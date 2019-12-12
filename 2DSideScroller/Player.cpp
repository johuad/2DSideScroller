#include "Player.h"

Player::Player()
{	
	texture.loadFromFile("spritesheet.png");
	sprite.setTexture(texture);
}

Player::~Player()
{
}

b2Body * Player::createBody(b2World * world, float x, float y)
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
	fixtureDef.friction = 0.3f;
	//set fixture restitution
	fixtureDef.restitution = 0;
	//apply fixture to body
	body->CreateFixture(&fixtureDef);

	//foot sensor fixture
	dynamicBox.SetAsBox(9.5f, 2.5f, b2Vec2(0.f, 20.f), 0);
	fixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = body->CreateFixture(&fixtureDef);
	footSensorFixture->SetUserData((void*)3);

	//get body mass
	mass = body->GetMass();
	//get body position
	position = body->GetPosition();
	//get body velocity
	velocity = body->GetLinearVelocity();

	initX = x;
	initY = y;

	return body;
}

void Player::setHP()
{
	hitPoints--;
}

int Player::getHP()
{
	return hitPoints;
}

void Player::destroy(b2Body *)
{
	body->SetTransform(b2Vec2(initX, initY), body->GetAngle());
	hitPoints = 100;
}

sf::Sprite Player::getSprite(b2Body * body)
{
	sprite.setTextureRect(sf::IntRect(0, 0, 20, 40));
	sprite.setPosition(body->GetPosition().x, body->GetPosition().y);
	sprite.setOrigin(10.f, 20.f);
	return sprite;
}

void Player::moveY(b2Body * body)
{
	float impulse = mass * -100.f;
	body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);
}

void Player::moveX(b2Body * body, float impulse)
{
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
}
