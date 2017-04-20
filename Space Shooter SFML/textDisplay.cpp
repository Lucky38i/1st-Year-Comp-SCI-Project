#include "textDisplay.h"
#pragma warning(disable: 4996)


textDisplay::textDisplay()
{
	text.setString(myString);
	text.setColor(sf::Color::Red);
	text.setCharacterSize(30);
	rect.setFillColor(sf::Color::Red);
	rect.setSize(sf::Vector2f(20, 20));
}

void textDisplay::update()
{
	text.move(0, -movementSpeed);

	counter++;
	if (counter >= lifeTime)
	{
		destroy = true;
	}
}

void textDisplay::rectUpdate()
{
	rect.setPosition(sf::Vector2f(text.getPosition().x, text.getPosition().y));
	rect.setSize(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height+15));
}

