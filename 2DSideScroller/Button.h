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

	//Font & text for the button.
	sf::Font font;
	sf::Text text;

public:
	Button();
	~Button();

	void GenerateButton(std::string id, float x, float y, float w, float h);
	sf::RectangleShape GetButton();
	sf::Text GetText();
	bool ButtonClicked(float x, float y);
	std::string GetButtonID();
};

