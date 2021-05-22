#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Button
{
private:
	//SF rectangle for the button.
	sf::RectangleShape rect;
	
	//ID of the button.
	std::string id = "";

public:
	Button();
	~Button();

	void GenerateButton(std::string, float, float, float, float);
	sf::RectangleShape GetButton();
	bool ButtonClicked(float, float);
	std::string GetButtonID();
};

