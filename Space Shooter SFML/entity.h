#pragma once
#ifndef __entity__
#define __entity__

#include <stdio.h>
#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>
#include <xtgmath.h>
#include <vector>
#include <functional>

#include <SFML\Main.hpp>
#include <SFML\Config.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <list>

using namespace std;

class entity
{
public:

	//Physical Object
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Text text;

	entity();

};

#endif /*__entity__*/
