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
}

sf::RectangleShape Button::GetButton()
{
	return rect;
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
