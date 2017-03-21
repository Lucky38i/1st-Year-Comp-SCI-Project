#include "projectile.h"

projectile::projectile()
{
	rect.setSize(sf::Vector2f(14, 22));
	//rect.setOrigin(sf::Vector2f(38 / 2, 34 / 2));
	rect.setPosition(0,0);
	rect.setFillColor(sf::Color::Green);
	
}

void projectile::update()
{

	//sprite.setTextureRect(sf::IntRect(0 * 14, 0, 14, 22));
	if (direction == 1) //Up
	{
		rect.move(0, -movementSpeed);
	}
	if (direction == 2) //Down
	{
		rect.move(0, movementSpeed);
	}

	counterLife++;
	if (counterLife >= lifeTime)
	{
		destroy = true;
	}

	sprite.setPosition(rect.getPosition());
}

void projectile::updateAnimation()
{
	sprite.setTextureRect(sf::IntRect(counterAnimation * 14, 0, 14, 22));
	counterAnimation++;
	if (counterAnimation >= 2)
	{
		counterAnimation = 2;
	}
}