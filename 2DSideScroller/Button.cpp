#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::GenerateButton(std::string id, float x, float y, float w, float h)
{
	this->id = id;

	rect.setSize(sf::Vector2f(w, h));
	rect.setPosition(sf::Vector2f(x, y));
	rect.setOrigin(w / 2, h / 2);
	rect.setFillColor(sf::Color(120, 120, 120, 255));
	rect.setOutlineColor(sf::Color::Black);

	//load font file
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);

	//Set button text.
	text.setString(id);
	text.setPosition(rect.getGlobalBounds().left + text.getLocalBounds().width, 
		rect.getGlobalBounds().top + text.getLocalBounds().height);
	
}

sf::RectangleShape Button::GetButton()
{
	return rect;
}

sf::Text Button::GetText()
{
	return text;
}

bool Button::ButtonClicked(float x, float y)
{
	if (rect.getGlobalBounds().contains(sf::Vector2f(x, y)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::string Button::GetButtonID()
{
	return id;
}
