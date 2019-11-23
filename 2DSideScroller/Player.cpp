#include "Player.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

Player::Player()
{	
}

Player::~Player()
{
}

b2Body * Player::createBody(b2World *world, float x, float y)
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
	fixtureDef.density = 1.0f;
	//set friction of our fixture
	fixtureDef.friction = 0.3f;
	//set fixture restitution
	fixtureDef.restitution = 0;
	//apply fixture to body
	body->CreateFixture(&fixtureDef);

	mass = body->GetMass();

	position = body->GetPosition();
	velocity = body->GetLinearVelocity();

	return body;
}

void Player::moveUp(b2Body *body)
{
	float impulse = mass * -100.f;
	body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);
}

void Player::moveX(b2Body *body, float impulse)
{
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
}

sf::RectangleShape Player::drawable(b2Body *body)
{
	position = body->GetPosition();
	//creates & defines rectangle for player position
	sf::RectangleShape rect(sf::Vector2f(20, 50));
	rect.setOrigin(10, 25);
	rect.setPosition(position.x, position.y);
	rect.setFillColor(sf::Color::Blue);

	return rect;
}
