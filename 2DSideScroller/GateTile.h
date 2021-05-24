#pragma once
#include "Tile.h"

class GateTile : public Tile
{
protected:
	std::string id = "gate";

	sf::Texture texture;

	sf::Sprite sprite;
public:
	GateTile(float r, float c, int x, int y, int sx, int sy);
	~GateTile();

	// Inherited via Tile
	virtual b2Body * returnBody() override;
	virtual std::string getID() override;
	virtual sf::Sprite returnSprite() override;
};

