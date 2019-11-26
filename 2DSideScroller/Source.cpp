#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Player.h"

int main()
{
	int width = 1280;
	int height = 720;

	sf::RenderWindow window(sf::VideoMode(width, height), "2DSideScroller");
	window.setFramerateLimit(60);

	sf::View view = window.getDefaultView();
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	view.zoom(0.5f);

	std::vector<sf::RectangleShape> levelTiles(200);

	b2Vec2 gravity(0.0f, 60.f);
	b2World world(gravity);

	float32 timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	b2BodyDef groundBodyDef;

	Player *newPlayer = new Player();

	b2Body *newPlayerBody;

	float initX = 0;
	float initY = 0;

	int level[10][40] =
	{
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
		{ 2, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
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
			else if (level[r][c] == 3)
			{
				initX = c * 50;
				initY = r * 50;
			}
		}
	}

	newPlayerBody = newPlayer->createBody(&world, initX, initY);
	
	int jumpTimer = 0;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		world.Step(timeStep, velocityIterations, positionIterations);

		float desiredVelocity = 0;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			jumpTimer++;
			if (jumpTimer < 10)
			{
				newPlayer->moveUp(newPlayerBody);
			}
		}

		if (newPlayerBody->GetLinearVelocity().y == 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			jumpTimer = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			desiredVelocity = -100;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			desiredVelocity = 100;
		}

		float velChange = desiredVelocity - newPlayerBody->GetLinearVelocity().x;
		float impulse = newPlayerBody->GetMass() * velChange;

		newPlayer->moveX(newPlayerBody, impulse);

		view.setCenter(newPlayerBody->GetPosition().x, newPlayerBody->GetPosition().y);
		view.move(0, -2 * 50);

		window.setView(view);
		window.clear(sf::Color::White);
		for (auto& tile : tiles)
		{
			window.draw(tile);
		}
		window.draw(newPlayer->drawable(newPlayerBody));
		window.display();
	}

	delete newPlayer;
	
	return 0;
}