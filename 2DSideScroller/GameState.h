#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class GameState
{
public:
	virtual void Draw(sf::RenderWindow &, const float) = 0;
	virtual void Update(const float) = 0;
	virtual void HandleInput(sf::RenderWindow &, sf::Event) = 0;
};


