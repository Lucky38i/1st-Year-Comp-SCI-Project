#include "enemy.h"
#include "random.h"



enemy::enemy()
{
	rect.setSize(sf::Vector2f(64, 47));
	//rect.setOrigin(sf::Vector2f(64 / 2, 47 / 2));
	//rect.setPosition(sf::Vector2f(500 / 2, 800 - 80));
	rect.setFillColor(sf::Color::Blue);

}


void enemy::update()
{
	sprite.setPosition(rect.getPosition());
	//sprite.setOrigin(rect.getOrigin());
	sprite.setRotation(180);

	counterLife++;
	if (counterLife >= lifeTime)
	{
		alive = false;
	}
}


void enemy::updateMovement()
{
	
	rect.move(0, downSpeed);

	if (canMoveLeft == true)
	{
		if (direction == 1) //Left
		{
			rect.move(-movementSpeed, 0);

		}
	}
	if (canMoveRight == true)
	{
		if (direction == 2) //Right
		{
			rect.move(movementSpeed, 0);
		}
	}

	counter++;
	if (counter >= 40)
	{
		direction = generateRandom(3);
		downSpeed = generateRandomFloat(0.5, 3.0);
		counter = 0;
	}
	
}

void enemy::wallCollision(const int max_width, int dimensions)
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