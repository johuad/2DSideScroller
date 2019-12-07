#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::generateLevel(b2World * world, std::vector<sf::RectangleShape> * tiles, std::string fileName, int row, int col)
{
	//ground body def for ground tiles
	b2BodyDef groundBodyDef;

	//select file to read
	std::ifstream levelFile{ fileName };

	//dynamically allocate 2d array for level generation
	level = new int*[row];
	for (int i = 0; i < row; i++)
	{
		level[i] = new int[col];
	}

	//read level information from file and store it in 2d array
	for (int i{}; i < row; i++)
	{
		for (int j{}; j < col; j++)
		{
			levelFile >> level[i][j];
		}
	}

	//generate level
	for (int c = 0; c < col; c++)
	{
		for (int r = 0; r < row; r++)
		{
			//"ground" tiles.
			if (level[r][c] == 1)
			{
				groundBodyDef.position.Set(c * 50.f, r * 50.f);

				b2Body* groundBody = world->CreateBody(&groundBodyDef);

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
				tiles->push_back(rect);
			}
			//world borders
			else if (level[r][c] == 2)
			{
				groundBodyDef.position.Set(c * 50.f, r * 50.f);

				b2Body* groundBody = world->CreateBody(&groundBodyDef);

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
				tiles->push_back(rect);
			}
		}
	}
}

float Level::getInitX()
{
	return initX;
}

float Level::getInitY()
{
	return initY;
}
