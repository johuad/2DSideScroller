#include "Game.h"

Game::Game(sf::RenderWindow &window, std::string levelName)
{
	//set up & initialize a view.
	sf::View view = window.getDefaultView();
	//set up viewport
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	//set zoom level
	view.zoom(0.5f);

	//set timeStep for Box2D physics simulation
	float32 timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	b2Vec2 gravity(0.0f, 100.f);
	b2World world(gravity);

	ContactListener worldContactListener;

	world.SetContactListener(&worldContactListener);

	std::vector<b2Body *> bodies(800);

	std::vector<Tile*> tiles;

	Level level = Level();

	level.generateLevel(&world, &tiles, levelName, 10, 80);

	//player object
	Player newPlayer = Player();

	//uninitialized body for player
	b2Body *newPlayerBody;

	//create a new body for our player.
	newPlayerBody = newPlayer.createBody(&world, level.getInitX(), level.getInitY());

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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (worldContactListener.numFootContacts > 0)
			{
				newPlayer.moveUp(newPlayerBody);
			}
		}

		//desired velocity
		float desiredVelocity = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			desiredVelocity = -100;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			desiredVelocity = 100;
		}

		//set up impulse for constant x-plane movement
		float velChange = desiredVelocity - newPlayerBody->GetLinearVelocity().x;
		float impulse = newPlayerBody->GetMass() * velChange;

		//move the player
		newPlayer.moveX(newPlayerBody, impulse);

		for (auto& t : tiles)
		{
			if (t->getID() == "lava")
			{
				if (newPlayer.drawable(newPlayerBody).getGlobalBounds().intersects(t->returnSprite().getGlobalBounds()))
				{
					//player takes damage if they fall into a hazard
					newPlayer.takeDamage();

					if (newPlayer.getHitPoints() < 0)
					{
						newPlayer.death(newPlayerBody);
						std::cout << world.GetBodyCount() << std::endl;

						std::cout << "Tiles cleared." << std::endl;

						std::cout << world.GetBodyCount() << std::endl;
					}
				}
			}
			if (t->getID() == "goal")
			{
				if (newPlayer.drawable(newPlayerBody).getGlobalBounds().intersects(t->returnSprite().getGlobalBounds()))
				{
					Game level2 = Game(window, "level2.txt");
				}
			}
		}

		//set view center
		view.setCenter(newPlayerBody->GetPosition().x, newPlayerBody->GetPosition().y);
		//move view along w/ player, with an offset on the Y plane.
		view.move(0, -1.25f * 50);

		//set the view
		window.setView(view);
		//set the clear color
		window.clear(sf::Color::Blue);
		//draw tiles
		for (auto& t : tiles)
		{
			window.draw(t->returnSprite());
		}
		//draw player
		window.draw(newPlayer.drawable(newPlayerBody));
		//display everything
		window.display();
	}
}

Game::~Game()
{
}
