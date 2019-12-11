#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::generateLevel(b2World * world, std::vector<Tile*> * tiles, std::string fileName, int row, int col)
{
	//select file to read
	std::ifstream levelFile{ fileName };

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
			//world borders
			if (level[r][c] == 1)
			{
				//just using a blank tile and pointing it at the transparent part of the sheet
				GroundTile * tile = new GroundTile(world, c * 50.f, r * 50.f, 51, 51, 50, 50);

				tiles->push_back(tile);
			}
			//top ground
			else if (level[r][c] == 2)
			{
				GroundTile * tile = new GroundTile(world, c * 50.f, r * 50.f, 51, 0, 50, 50);

				tiles->push_back(tile);
			}
			//mid ground
			else if (level[r][c] == 3)
			{
				GroundTile * tile = new GroundTile(world, c * 50.f, r * 50.f, 0, 0, 50, 50);

				tiles->push_back(tile);
			}
			//lava
			else if (level[r][c] == 4)
			{
				LavaTile * tile = new LavaTile(c * 50.f, r * 50.f, 0, 51, 50, 50);

				tiles->push_back(tile);
			}
			//goal
			else if (level[r][c] == 5)
			{
				GoalTile * tile = new GoalTile(c * 50.f, r * 50.f, 0, 0, 50, 50);

				tiles->push_back(tile);
			}
			//player spawn
			else if (level[r][c] == 6)
			{
				initX = c * 50.f;
				initY = r * 50.f;
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
