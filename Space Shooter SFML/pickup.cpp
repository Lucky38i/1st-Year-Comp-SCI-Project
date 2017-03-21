#include "pickup.h"

pickup::pickup()
{
	rect.setSize(sf::Vector2f(20, 20));
	rect.setPosition(sf::Vector2f(0, 0));
	rect.setFillColor(sf::Color::Blue);
	sprite.setTextureRect(sf::IntRect(0, 0, 20, 20));
}

void pickup::update()
{
	sprite.setPosition(rect.getPosition());
	rect.move(sf::Vector2f(0, dropSpeed));
}

void pickup::animate()
{
	sprite.setTextureRect(sf::IntRect(20*counter, 0, 20, 20));
	counter++;
	if (counter == 4)
	{
		counter = 0;
	}

}
