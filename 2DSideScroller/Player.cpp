#include "Player.h"

Player::Player()
{	
	hitPoints = 100;

	lastDirection = 1;
	
	moveLeft = false;
	moveRight = false;

	texture.loadFromFile("spritesheet.png");
	
	sprite.setTexture(texture);
}

Player::~Player()
{
}

void Player::setHP()
{
	hitPoints--;
}

int Player::getHP()
{
	return hitPoints;
}

b2Body *Player::createBody(b2World *world, float x, float y)
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

	//Define & create Box2D fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 0;
	body->CreateFixture(&fixtureDef);

	//Define & create Box2D Foot Sensor fixture.
	dynamicBox.SetAsBox(2.45f, 2.5f, b2Vec2(0.f, 20.f), 0);
	fixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = body->CreateFixture(&fixtureDef);
	footSensorFixture->SetUserData((void*)3);

	mass = body->GetMass();
	position = body->GetPosition();
	velocity = body->GetLinearVelocity();

	initX = x;
	initY = y;

	return body;
}

void Player::destroy(b2Body *)
{
	body->SetTransform(b2Vec2(initX, initY), body->GetAngle());
	hitPoints = 100;
}

sf::Sprite Player::getSprite(b2Body * body)
{
	return sprite;
}

void Player::moveY(b2Body * body)
{
	float impulse = mass * -100.f;
	body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);
}

void Player::moveX(b2Body * body, float impulse)
{
	if (lastDirection == 1)
	{
		bool moveRight = true;
		if (moveRight)
		{
			sprite.setTextureRect(sf::IntRect(80, 0, 20, 40));
			sprite.setPosition(body->GetPosition().x, body->GetPosition().y);
			sprite.setOrigin(10.f, 20.f);
			moveRight = false;
		}
	}
	else if (lastDirection == 0)
	{
		bool moveLeft = true;
		if (moveLeft)
		{
			sprite.setTextureRect(sf::IntRect(60, 0, 20, 40));
			sprite.setPosition(body->GetPosition().x, body->GetPosition().y);
			sprite.setOrigin(10.f, 20.f);
			moveLeft = false;
		}
	}
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
}

void Player::setLastDirection(int i)
{
	lastDirection = i;
}

int Player::getLastDirection()
{
	return lastDirection;
}


void Player::FireBullet()
{
	// firing bullet*/
	if (bullets.size() < 1)
	{
		int speed = 3;
		if (getLastDirection() == 1)
		{
			speed = speed * 1;
		}
		else if (getLastDirection() == 0)
		{
			speed = speed * -1;
		}
		Bullet bullet = Bullet(speed);
		bullet.setPos(sf::Vector2f(body->GetPosition().x, body->GetPosition().y));
		bullets.push_back(bullet);
	}
}
