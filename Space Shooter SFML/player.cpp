#include "player.h"



player::player()
{
	rect.setSize(sf::Vector2f(38, 34));
	rect.setOrigin(sf::Vector2f(38 / 2, 34 / 2));
	rect.setPosition(sf::Vector2f(500 / 2, 800 - 80));
	rect.setFillColor(sf::Color::Blue);

}

void player::update()
{
	sprite.setPosition(rect.getPosition());
	sprite.setOrigin(rect.getOrigin());
}

void player::updateMovement()
{
	//rect.move(0, -movementSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (canMoveLeft == true)
		{
			rect.move(-movementSpeed, 0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (canMoveRight == true)
		{
			rect.move(movementSpeed, 0);
		}
		
	}
}

void player::wallCollision(const int max_width, int dimensions)
{
	if (rect.getPosition().x <= dimensions)
	{
		canMoveLeft = false;
	}
	else if (rect.getPosition().x >= max_width - dimensions)
	{
		canMoveRight = false;
	}
	else
	{
		canMoveLeft = true;
		canMoveRight = true;
	}

}



