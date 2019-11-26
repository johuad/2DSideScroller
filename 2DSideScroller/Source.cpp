#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Player.h"

int main()
{
	//window dimensions
	int width = 1280;
	int height = 720;

	//set up window & window title.
	sf::RenderWindow window(sf::VideoMode(width, height), "2DSideScroller");
	//limit framerate
	window.setFramerateLimit(60);

	//set up & initialize a view.
	sf::View view = window.getDefaultView();
	//set up viewport
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	//set zoom level
	view.zoom(0.4f);

	//set timeStep for Box2D physics simulation
	float32 timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	b2Vec2 gravity(0.0f, 60.f);
	b2World world(gravity);

	//ground tile definition
	b2BodyDef groundBodyDef;

	//pointer to player object.
	Player *newPlayer = new Player();

	//uninitialized body for player
	b2Body *newPlayerBody;

	//initial position variables
	float initX = 0;
	float initY = 0;

	//level structure
	int level[10][40] =
	{
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	};

	//storage for level.
	std::vector<sf::RectangleShape> tiles(400);

	//generate level
	for (int c = 0; c < 40; c++)
	{
		for (int r = 0; r < 10; r++)
		{
			//"ground" tiles.
			if (level[r][c] == 1)
			{
				groundBodyDef.position.Set(c * 50.f, r * 50.f);

				b2Body* groundBody = world.CreateBody(&groundBodyDef);

				b2PolygonShape groundBox;
				groundBox.SetAsBox(25.0f, 25.0f);
				//groundBody->CreateFixture(&groundBox, 0.0f);

				b2FixtureDef fixtureDef;

				fixtureDef.shape = &groundBox;
				fixtureDef.density = 0.0f;
				fixtureDef.friction = 0.f;

				groundBody->CreateFixture(&fixtureDef);

				b2Vec2 groundPos = groundBody->GetPosition();

				sf::RectangleShape rect(sf::Vector2f(50, 50));
				rect.setOrigin(sf::Vector2f(25, 25));
				rect.setPosition(groundPos.x, groundPos.y);
				rect.setFillColor(sf::Color::Black);
				tiles.push_back(rect);
			}
			//world borders
			else if (level[r][c] == 2)
			{
				groundBodyDef.position.Set(c * 50.f, r * 50.f);

				b2Body* groundBody = world.CreateBody(&groundBodyDef);

				b2PolygonShape groundBox;
				groundBox.SetAsBox(25.0f, 25.0f);
				//groundBody->CreateFixture(&groundBox, 0.0f);

				b2FixtureDef fixtureDef;

				fixtureDef.shape = &groundBox;
				fixtureDef.density = 0.0f;
				fixtureDef.friction = 0.f;

				groundBody->CreateFixture(&fixtureDef);
			}
			//player spawn point.
			else if (level[r][c] == 3)
			{
				initX = c * 50.f;
				initY = r * 50.f;
			}
			else if (level[r][c] == 4)
			{
				sf::RectangleShape rect(sf::Vector2f(50, 50));
				rect.setOrigin(sf::Vector2f(25, 25));
				rect.setPosition(c * 50.f, r * 50.f);
				rect.setFillColor(sf::Color::Red);
				tiles.push_back(rect);
			}
		}
	}

	//create a new body for our player.
	newPlayerBody = newPlayer->createBody(&world, initX, initY);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		world.Step(timeStep, velocityIterations, positionIterations);

		//keyboard inputs
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (!newPlayerBody->GetContactList() == 0)
			{
				newPlayer->moveUp(newPlayerBody);
			}
		}

		//desired velocity
		float desiredVelocity = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			desiredVelocity = -100;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			desiredVelocity = 100;
		}

		//set up impulse for constant x-plane movement
		float velChange = desiredVelocity - newPlayerBody->GetLinearVelocity().x;
		float impulse = newPlayerBody->GetMass() * velChange;

		//move the player
		newPlayer->moveX(newPlayerBody, impulse);

		for (auto& tile : tiles)
		{
			if (tile.getFillColor() == sf::Color::Red)
			{
				if (newPlayer->drawable(newPlayerBody).getGlobalBounds().intersects(tile.getGlobalBounds()))
				{
					//player takes damage if they fall into a hazard
					newPlayer->takeDamage();
					
					if (newPlayer->getHitPoints() < 0)
					{
						newPlayer->death(newPlayerBody);
					}
				}
			}
		}

		//set view center
		view.setCenter(newPlayerBody->GetPosition().x, newPlayerBody->GetPosition().y);
		//move view along w/ player, with an offset on the Y plane.
		view.move(0, -2 * 50);

		//set the view
		window.setView(view);
		//set the clear color
		window.clear(sf::Color::White);
		//draw tiles
		for (auto& tile : tiles)
		{
			window.draw(tile);
		}
		//draw player
		window.draw(newPlayer->drawable(newPlayerBody));
		//display everything
		window.display();
	}
	//delete newPlayer object.
	delete newPlayer;

	return 0;
}