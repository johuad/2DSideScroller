#pragma once
#include "Tile.h"
class GoalTile : public Tile
{
protected:
	std::string id = "goal";

	sf::Texture texture;

	sf::Sprite sprite;
public:
	GoalTile(float r, float c, int x, int y, int sx, int sy);
	~GoalTile();

	// Inherited via Tile
	virtual b2Body * returnBody() override;
	virtual std::string getID() override;
	virtual sf::Sprite returnSprite() override;
};

