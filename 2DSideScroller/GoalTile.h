#pragma once
#include "Tile.h"
class GoalTile : public Tile
{
protected:
	std::string id = "goal";

	sf::Texture texture;

	sf::Sprite sprite;
public:
	GoalTile(float, float, int, int, int, int);
	~GoalTile();

	// Inherited via Tile
	virtual b2Body * returnBody() override;
	virtual std::string getID() override;
	virtual sf::Sprite returnSprite() override;
};

