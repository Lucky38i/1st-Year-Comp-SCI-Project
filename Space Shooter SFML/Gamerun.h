#pragma once
#ifndef  __Gamerun__
#define __Gamerun__

#pragma warning(disable:4996)

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>

//External entities
#include <SFML/Graphics.hpp>
#include <SFML/window.hpp>
#include <SFML/Audio.hpp>
#include "player.h"
#include "entity.h"
#include "projectile.h"
#include "enemy.h"
#include "random.h"
#include "textDisplay.h"
#include "pickup.h"
#include "hud.h"
#include "Particles.h"

using namespace sf;
using std::cout;
using std::endl;
using std::string;




class Gamerun
{
public:
	
	//Structures
	struct enemyDetails
	{
		string name;
		int dimensionx;
		int dimensiony;
	};

	//Variables
	const int MAX_HEIGHT = 800;
	const int MAX_WIDTH = 500;
	sf::Clock projectileClock;
	sf::Clock projectileClock1;
	sf::Clock collisionClock;
	sf::Clock PickupClock;
	sf::Clock particleClock;
	int universalCounter = 0;
	int counter2 = 0;
	int counter3 = 0;
	int enemyX;
	int enemyY;
	int dropChance = 3;
	enemyDetails ENEMY_SHIPS[4];
	

	Gamerun();
	void run();
	Texture textureLoad(string filename);
	Font fontLoad(string filename);


};

#endif // ! __Gamerun__
