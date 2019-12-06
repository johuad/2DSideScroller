#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Player.h"
#include "Level.h"
#include "ContactListener.h"

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
	//view.zoom(0.5f);
	view.zoom(5.f); //debug zoom

	//set timeStep for Box2D physics simulation
	float32 timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	b2Vec2 gravity(0.0f, 60.f);
	b2World world(gravity);

	ContactListener worldContactListener;

	world.SetContactListener(&worldContactListener);

	std::vector<sf::RectangleShape> tiles(400);

	Level *level = new Level();

	level->generateLevel(&world, &tiles, "level1.txt", 10, 80);

	//player object
	Player *newPlayer = new Player();

	//uninitialized body for player
	b2Body *newPlayerBody;

	//create a new body for our player.
	newPlayerBody = newPlayer->createBody(&world, level->getInitX(), level->getInitY());

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
			if (worldContactListener.numFootContacts > 0)
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

	delete level;

	return 0;
}