#include "Menu.h"

Menu::Menu(sf::RenderWindow &window)
{
	//set up & initialize a view.
	sf::View view = window.getDefaultView();

	std::vector<std::string> levels(0);
	std::vector<sf::Text> levelText(0);

	std::ifstream levelManifest{ "levelmanifest.txt" };
	std::string str;
	while (std::getline(levelManifest, str))
	{
		levels.push_back(str);
	}

	font.loadFromFile("arial.ttf");

	//list levels in manifest
	for (int i = 0; i < 3; i++)
	{
		text.setFont(font);
		text.setCharacterSize(25);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Bold);
		text.setPosition(0.25, 0.f + (i * 25.f));
		text.setLineSpacing(1.f);
		text.setString(levels.at(i));
		levelText.push_back(text);
	}

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//keyboard in puts for now
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			level1 = new Game(window, "level1.txt");
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			level2 = new Game(window, "level2.txt");
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			std::exit(0);
		}

		//clear screen, set white
		window.clear(sf::Color::White);
		//draw text
		for (auto& t : levelText)
		{
			window.draw(t);
		}
		//display everything
		window.display();
	}
}

Menu::~Menu()
{
}
