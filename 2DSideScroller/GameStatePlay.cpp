#include "GameStatePlay.h"

GameStatePlay::GameStatePlay(Game *game, std::string levelName)
{
	this->game = game;
	
	velocityIterations = 6;
	positionIterations = 2;

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

	//set current level (file name)
	curLevel = levelName;

	//generate level
	level.generateLevel(world, &tiles, levelName, 10, 80);

	//create a new body for our player.
	playerBody = player->createBody(world, level.getInitX(), level.getInitY());

	//create a new body for the enemy
	enemyBody = enemy->createBody(world, level.getInitXE(), level.getInitYE());

	//create a new body for the obstacle
	obstacleBody = obstacle->createBody(world, level.getInitXO(), level.getInitYO());

	//Get the current level count.
	levelCount = GetLevelCount(curLevel);
}

GameStatePlay::~GameStatePlay()
{
}

void GameStatePlay::SetupUI(sf::RenderWindow & window)
{

}

void GameStatePlay::Draw(sf::RenderWindow & window, const float delta)
{
	window.clear(sf::Color::Blue);

	//Draw all of our tiles.
	for (auto& t : tiles)
	{
		window.draw(t->returnSprite());
	}

	//Draw bullets.
	for (auto& b : player->bullets)
	{
		window.draw(b.getBullet());
		b.fire();
	}

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

	//Draw the text of our HP counter
	window.draw(text);

	//Draw player
	window.draw(player->getSprite(playerBody));

	//draw enemy
	window.draw(enemy->getSprite(enemyBody));
	//draw obstacle
	window.draw(obstacle->getSprite(obstacleBody));

	//Set up viewport.
	sf::View view = window.getDefaultView();
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	view.zoom(0.5f);
	view.setCenter(playerBody->GetPosition().x, playerBody->GetPosition().y);
	view.move(0, -1.25f * 50);

	//Set the viewport.
	window.setView(view);
}

void GameStatePlay::Update(const float delta)
{
	//Set world step.
	world->Step(delta, velocityIterations, positionIterations);

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
					player->destroy(playerBody);
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
				std::exit(0);
			}
		}
	}

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
				impulse = impulse * 1;
			}
			else if (b.getDirection() < 0)
			{
				impulse = impulse * -1;
			}
			enemy->moveX(enemyBody, impulse);
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
