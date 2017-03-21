#include "hud.h"

hud::hud()
{
	rect.setSize(sf::Vector2f(98, 32));
	rect.setPosition(sf::Vector2f(0, 0));
	rect.setFillColor(sf::Color::Blue);
	//sprite.setTextureRect(sf::IntRect(0, 0, 78, 26));
}

void hud::update()
{
	sprite.setPosition(rect.getPosition());
}

void hud::updateHealth()
{
	sprite.setTextureRect(sf::IntRect(0, 0, picWidth - math*damage, 18));
}

