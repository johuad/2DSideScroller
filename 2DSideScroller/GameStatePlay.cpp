#include "GameStatePlay.h"

GameStatePlay::GameStatePlay(std::shared_ptr<Game> game, std::string levelName)
{
	this->game = game;

	//Initialize Box2D world and attach contact listener.
	world = new b2World(b2Vec2(0.0f, 100.0f));
	world->SetContactListener(&worldContactListener);

	//load font file
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setCharacterSize(10);
	text.setFillColor(sf::Color::Green);
	text.setStyle(sf::Text::Bold);

	//Initialize entities.
	player = new Player();
	enemy = new Enemy();
	obstacle = new Obstacle();

	//Set firing to false.
	isFiring = false;

	//Set current level (file name)
	curLevel = levelName;

	//Generate level
	level = Level(world, &tiles, levelName, 10, 80);

	//Create a new body for our player.
	playerBody = player->createBody(world, level.getInitX(), level.getInitY());

	//Create a new body for the enemy
	enemyBody = enemy->createBody(world, level.getInitXE(), level.getInitYE());

	//Create a new body for the obstacle
	obstacleBody = obstacle->createBody(world, level.getInitXO(), level.getInitYO());

	//Get the current level count.
	levelCount = GetLevelCount(curLevel);

	//Add one to the level count.
	levelCount = levelCount + 1;

	//Get the name of the next level.
	nextLevel = "level" + std::to_string(levelCount) + ".txt";
	
	//Initialize "last level".
	lastLevel = "";

	//Open the level manifest.
	manifest.open("levelmanifest.txt");

	//Go through each line in the manifest and push it into the list.
	while (std::getline(manifest, line))
	{
		levelManifest.push_back(line);
	}

	//If nextLevel isn't found in the manifest, the current level is the last level.
	if (!std::count(levelManifest.begin(), levelManifest.end(), nextLevel))
	{
		lastLevel = curLevel;
	}
}

GameStatePlay::~GameStatePlay()
{
}

void GameStatePlay::Draw(sf::RenderWindow & window, const float delta)
{
	//Set up viewport.
	view = window.getDefaultView();
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	view.zoom(0.5f);
	view.setCenter(playerBody->GetPosition().x, playerBody->GetPosition().y);
	view.move(0, -1.25f * 50);

	//Set the viewport.
	window.setView(view);

	//Clear color (and also lazily set up background for the game).
	window.clear(sf::Color::Blue);

	//Set up our "health meter"
	std::string playerHealth = "HP: " + std::to_string(player->getHP());
	text.setString(playerHealth);
	text.setPosition(playerBody->GetPosition().x - 20, playerBody->GetPosition().y - 70);

	//Change color of the health counter based on health.
	if (player->getHP() < 25)
	{
		text.setFillColor(sf::Color::Red);
	}
	else
	{
		text.setFillColor(sf::Color::Green);
	}


	//Draw all of our tiles.
	for (auto& t : tiles)
	{
		window.draw(t->returnSprite());
	}

	//Draw entities.
	window.draw(player->getSprite(playerBody));
	window.draw(enemy->getSprite(enemyBody));
	window.draw(obstacle->getSprite(obstacleBody));

	//Draw the text of our HP counter
	window.draw(text);

	//Draw bullets.
	for (auto& b : player->bullets)
	{
		window.draw(b.getBullet());
		b.fire();
	}

}

void GameStatePlay::Update(const float delta)
{
	//Set world step.
	world->Step(delta, velocityIterations, positionIterations);

	//Fire bullets.
	for (auto& b : player->bullets)
	{
		for (auto& t : tiles)
		{
			if (b.getBullet().getGlobalBounds().intersects(t->returnSprite().getGlobalBounds()))
			{
				player->bullets.pop_back();
			}
		}

		if (b.getBullet().getGlobalBounds().intersects(enemy->getSprite(enemyBody).getGlobalBounds()))
		{
			float impulse = 10000;
			player->bullets.pop_back();

			if (b.getDirection() > 0)
			{
				impulse = impulse * 1 * delta;
			}
			else if (b.getDirection() < 0)
			{
				impulse = impulse * -1 * delta;
			}
			enemy->moveX(enemyBody, impulse);
		}
	}

	//Check for special tiles.
	for (auto &t : tiles)
	{
		if (t->getID() == "lava")
		{
			if (player->getSprite(playerBody).getGlobalBounds().intersects(t->returnSprite().getGlobalBounds()))
			{
				//player takes damage if they fall into a hazard
				player->setHP();

				if (player->getHP() < 0)
				{
					game->ChangeState(std::shared_ptr<GameStateMenu>(new GameStateMenu(game)));
				}
			}
		}

		if (t->getID() == "goal")
		{
			if (enemy->getSprite(enemyBody).getGlobalBounds().intersects(t->returnSprite().getGlobalBounds()))
			{
				world->DestroyBody(enemyBody);
				world->DestroyBody(obstacleBody);
			}
		}

		if (t->getID() == "gate")
		{
			if (player->getSprite(playerBody).getGlobalBounds().intersects(t->returnSprite().getGlobalBounds()))
			{
				if (lastLevel == curLevel)
				{
					//game->ChangeState(std::shared_ptr<GameStateMenu>(new GameStateMenu(game)));
					std::exit(0);
				}
				else
				{
					//Move to the next level.
					game->ChangeState(std::shared_ptr<GameStatePlay>(new GameStatePlay(game, nextLevel)));
				}
			}
		}
	}
}

void GameStatePlay::HandleInput(sf::RenderWindow & window, sf::Event event)
{
	//keyboard inputs
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (worldContactListener.numFootContacts > 0)
		{
			player->moveY(playerBody);
		}
	}

	//desired velocity
	float desiredVelocity = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		desiredVelocity = -100;
		player->setLastDirection(0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		desiredVelocity = 100;
		player->setLastDirection(1);
	}

	//Impulse for constant rate of movement.
	float velChange = desiredVelocity - playerBody->GetLinearVelocity().x;
	float impulse = playerBody->GetMass() * velChange;

	//Move the player left or right
	player->moveX(playerBody, impulse);

	
	//Fire a bullet.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		isFiring = true;
		player->FireBullet();
	}
	
}

int GameStatePlay::GetLevelCount(std::string i)
{
	//Find the first integer in the string.
	auto n = i.find_first_of("0123456789");

	//Level count.
	int lc;

	//Try to create a string that will point us to the next level.
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
