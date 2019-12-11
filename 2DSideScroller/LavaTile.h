#pragma once
#include "Tile.h"
class LavaTile : public Tile
{
protected:
	std::string id = "lava";

	sf::Texture texture;
	
	sf::Sprite sprite;
public:
	LavaTile(float, float, int, int, int, int);
	~LavaTile();

	// Inherited via Tile
	virtual b2Body * returnBody() override;

	// Inherited via Tile
	virtual std::string getID() override;
	virtual sf::Sprite returnSprite() override;
};

