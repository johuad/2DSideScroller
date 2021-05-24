#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class GameState
{
public:
	virtual void Draw(sf::RenderWindow &window, const float delta) = 0;
	virtual void Update(const float delta) = 0;
	virtual void HandleInput(sf::RenderWindow &window, sf::Event event) = 0;
};


