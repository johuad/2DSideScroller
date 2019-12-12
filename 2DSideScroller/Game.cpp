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

	world.SetContactListener(&worldContactListener);

	//load font file
	font.loadFromFile("arial.ttf");
	//set text font
	text.setFont(font);
	//set character size
	text.setCharacterSize(10);
	//set fill color
	text.setFillColor(sf::Color::Green);
	//set style
	text.setStyle(sf::Text::Bold);

	//set current level (file name)
	curLevel = levelName;

	//generate level
	level.generateLevel(&world, &tiles, levelName, 10, 80);

	//create a new body for our player.
	playerBody = player.createBody(&world, level.getInitX(), level.getInitY());

	//create a new body for the enemy
	enemyBody = enemy.createBody(&world, level.getInitXE(), level.getInitYE());

	//create a new body for the obstacle
	obstacleBody = obstacle.createBody(&world, level.getInitXO(), level.getInitYO());
	
	// Define Bullet
	std::vector<Bullet> bullets;
	bool isFiring = false;

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
				player.moveY(playerBody);
			}
		}

		//desired velocity
		float desiredVelocity = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			desiredVelocity = -100;
			player.setLastDirection(0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			desiredVelocity = 100;
			player.setLastDirection(1);
		}

		//set up impulse for constant x-plane movement
		float velChange = desiredVelocity - playerBody->GetLinearVelocity().x;
		float impulse = playerBody->GetMass() * velChange;

		//move the player left or right
		player.moveX(playerBody, impulse);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			isFiring = true;
		}

		//initialize levelCount
		levelCount = getLevelCount(curLevel);

		for (auto& t : tiles)
		{
			if (t->getID() == "lava")
			{
				if (player.getSprite(playerBody).getGlobalBounds().intersects(t->returnSprite().getGlobalBounds()))
				{
					//player takes damage if they fall into a hazard
					player.setHP();

					if (player.getHP() < 0)
					{
						player.destroy(playerBody);
					}
				}
			}

			if (t->getID() == "goal")
			{
				if (player.getSprite(playerBody).getGlobalBounds().intersects(t->returnSprite().getGlobalBounds()))
				{
					levelCount++;
					std::string newLevel = "level" + std::to_string(levelCount) + ".txt";
					std::cout << newLevel << std::endl;

					Game newGame = Game(window, newLevel);
				}
			}

			if (t->getID() == "gate")
			{
				if (enemy.getSprite(enemyBody).getGlobalBounds().intersects(t->returnSprite().getGlobalBounds()))
				{
					world.DestroyBody(enemyBody);
					world.DestroyBody(obstacleBody);
				}
			}
		}

		for (auto& b : bullets)
		{
			for (auto& t : tiles)
			{
				if (b.getBullet().getGlobalBounds().intersects(t->returnSprite().getGlobalBounds()))
				{
					bullets.pop_back();
					isFiring = false;
				}
			}

			if (b.getBullet().getGlobalBounds().intersects(enemy.getSprite(enemyBody).getGlobalBounds()))
			{
				float impulse = 10000;
				bullets.pop_back();
				enemy.setHP();
				std::cout << enemy.getHP() << std::endl;

				if (enemy.getHP() < 0)
				{
					if (b.getDirection() > 0)
					{
						impulse = impulse * 1;
					}
					else if (b.getDirection() < 0)
					{
						impulse = impulse * -1;
					}
					enemy.moveX(enemyBody, impulse);
				}

				isFiring = false;
			}
		}

		//set view center
		view.setCenter(playerBody->GetPosition().x, playerBody->GetPosition().y);
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
		std::string playerHealth = "HP: " + std::to_string(player.getHP());
		text.setString(playerHealth);
		text.setPosition(playerBody->GetPosition().x - 20, playerBody->GetPosition().y - 40);
		if (player.getHP() < 25)
			text.setFillColor(sf::Color::Red);
		else
			text.setFillColor(sf::Color::Green);
		window.draw(text);
		//draw player
		window.draw(player.getSprite(playerBody));

		// firing bullet*/
		if (isFiring && bullets.size() < 1)
		{
			int speed = 3;
			if (player.getLastDirection() == 1)
			{
				speed = speed * 1;
			}
			else if (player.getLastDirection() == 0)
			{
				speed = speed * -1;
			}
			Bullet bullet = Bullet(speed);
			bullet.setPos(sf::Vector2f(playerBody->GetPosition().x, playerBody->GetPosition().y));
			bullets.push_back(bullet);
		}
		
		for (auto& b : bullets)
		{
			window.draw(b.getBullet());
			b.fire();
		}

		//draw enemy
		window.draw(enemy.getSprite(enemyBody));
		//draw obstacle
		window.draw(obstacle.getSprite(obstacleBody));
		//display everything
		window.display();
	}
}

Game::~Game()
{
}

int Game::getLevelCount(std::string i)
{	
	auto n = i.find_first_of("0123456789");

	int lc;

	try
	{
		if (std::string::npos != n)
		{
			lc = std::stoul(i.substr(n));
		}
	}
	catch (int e)
	{
		std::cout << "Exception: " << e << std::endl;
	}

	return lc;
}
