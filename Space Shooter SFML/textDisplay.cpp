#include "textDisplay.h"
#pragma warning(disable: 4996)


textDisplay::textDisplay()
{
	text.setString(myString);
	text.setColor(sf::Color::Red);
	text.setCharacterSize(30);
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

