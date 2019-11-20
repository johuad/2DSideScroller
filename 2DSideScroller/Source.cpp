#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

void main()
{
	int width = 1280;
	int height = 720;

	sf::RenderWindow window(sf::VideoMode(width, height), "2DSideScroller");
	window.setFramerateLimit(60);

	sf::View view = window.getDefaultView();
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	view.zoom(5.f);

	std::vector<sf::RectangleShape> levelTiles(200);

	b2Vec2 gravity(0.0f, -9.8f);
	b2World world(gravity);

	float32 timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	b2BodyDef groundBodyDef;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(3 * 50, 8 * 50);
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(25.0f, 25.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0;
	body->CreateFixture(&fixtureDef);

	int level[10][40] =
	{
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	};

	std::vector<sf::RectangleShape> tiles(400);

	for (int c = 0; c < 40; c++)
	{
		for (int r = 0; r < 10; r++)
		{
			if (level[r][c] == 1)
			{
				groundBodyDef.position.Set(c * 50, r * 50);

				b2Body* groundBody = world.CreateBody(&groundBodyDef);

				b2PolygonShape groundBox;
				groundBox.SetAsBox(25.0f, 25.0f);
				groundBody->CreateFixture(&groundBox, 0.0f);

				b2Vec2 groundPos = groundBody->GetPosition();

				sf::RectangleShape rect(sf::Vector2f(50, 50));
				rect.setOrigin(sf::Vector2f(25, 25));
				rect.setPosition(groundPos.x, groundPos.y);
				rect.setFillColor(sf::Color::Black);
				tiles.push_back(rect);
			}
			else if (level[r][c] == 2)
			{
				groundBodyDef.position.Set(c * 50, r * 50);

				b2Body* groundBody = world.CreateBody(&groundBodyDef);

				b2PolygonShape groundBox;
				groundBox.SetAsBox(25.0f, 25.0f);
				groundBody->CreateFixture(&groundBox, 0.0f);
			}
		}
	}

	int velocityX = 0;
	int velocityY = 0;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		world.Step(timeStep, velocityIterations, positionIterations);

		b2Vec2 position = body->GetPosition();
		float32 mass = body->GetMass();
		float32 angle = body->GetAngle();

		b2Vec2 velocity = body->GetLinearVelocity();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			velocityY = -100;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			velocityX = -100;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			velocityX = 100;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			velocityY = 0;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			velocityX = 0;
		}

		float xImpulse = body->GetMass() * velocityX;
		float yImpulse = body->GetMass() * velocityY;

		body->ApplyLinearImpulse(b2Vec2(xImpulse, yImpulse), body->GetWorldCenter(), true);

		sf::RectangleShape player(sf::Vector2f(50, 50));
		player.setOrigin(sf::Vector2f(25, 25));
		player.setPosition(position.x, position.y);
		player.setFillColor(sf::Color::Blue);

		view.setCenter(position.x, position.y);
		view.move(0, 0);

		window.setView(view);
		window.clear(sf::Color::White);
		for (auto& tile : tiles)
		{
			window.draw(tile);
		}
		window.draw(player);
		window.display();
	}
}
