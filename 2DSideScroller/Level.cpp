#include "Level.h"

Level::Level(b2World *world, std::vector<std::shared_ptr<Tile>> *tiles, std::string fileName, int row, int col)
{
	//select file to read
	std::ifstream levelFile;
	levelFile.open(fileName);

	//dynamically allocate 1d array for level generation
	level = new int*[row];
	for (int i = 0; i < row; i++)
	{
		level[i] = new int[col];
	}

	//read level information from file and store it in 1d array
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
			int tileType = level[r][c];

			switch (tileType) {
			case 1:
				//world borders
				tile = std::shared_ptr<Tile>(new GroundTile(world, c * 50.f, r * 50.f, 50, 100, 50, 50));

				tiles->push_back(tile);
				break;
			case 2:
				//top ground
				tile = std::shared_ptr<Tile>(new GroundTile(world, c * 50.f, r * 50.f, 100, 0, 50, 50));

				tiles->push_back(tile);
				break;
			case 3:
				//mid ground
				tile = std::shared_ptr<Tile>(new GroundTile(world, c * 50.f, r * 50.f, 50, 40, 50, 50));

				tiles->push_back(tile);
				break;
			case 4:
				//lava
				tile = std::shared_ptr<Tile>(new LavaTile(c * 50.f, r * 50.f, 100, 50, 60, 50));

				tiles->push_back(tile);
				break;
			case 5:
				//obstacle
				initXO = c * 50.f;
				initYO = r * 50.f;
				break;
			case 6:
				//gate
				tile = std::shared_ptr<Tile>(new GateTile(c * 50.f, r * 50.f, 0, 40, 50, 50));

				tiles->push_back(tile);
				break;
			case 7:
				//goal
				tile = std::shared_ptr<Tile>(new GoalTile(c * 50.f, r * 50.f, 100, 50, 50, 50));

				tiles->push_back(tile);
				break;
			case 8:
				//player spawn
				initX = c * 50.f;
				initY = r * 50.f;
				break;
			case 9:
				//enemy spawn
				initXE = c * 50.f;
				initYE = r * 50.f;
				break;
			}
		}
	}

	levelFile.close();
}

Level::Level()
{
}

Level::~Level()
{
}

float Level::getInitX()
{
	return initX;
}

float Level::getInitY()
{
	return initY;
}

float Level::getInitXE()
{
	return initXE;
}

float Level::getInitYE()
{
	return initYE;
}

float Level::getInitXO()
{
	return initXO;
}

float Level::getInitYO()
{
	return initYO;
}
