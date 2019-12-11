#pragma once
#include "Tile.h"
class GroundTile : public Tile
{
protected:
	std::string id = "ground";
	
	sf::Texture texture;

	sf::Sprite sprite;

	b2World * world;

	b2Body * body;
public:
	GroundTile(b2World *, float, float, int, int, int, int);
	~GroundTile();

	virtual b2Body * returnBody();

	// Inherited via Tile
	virtual std::string getID() override;

	// Inherited via Tile
	virtual sf::Sprite returnSprite() override;
};
