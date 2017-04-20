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
	double fireRate = 0.4;
	enemyDetails ENEMY_SHIPS[4];
	
	//Fixed Varibles
	string gameState = "Menu";
	sf::Clock projectileClock; //Clock for the projectile fire rate
	sf::Clock projectileClock1; // Clock for animation the projectile
	sf::Clock collisionClock; //Clock for the rate of player health lost
	sf::Clock PickupClock;	 //Clock for animating the pickup
	sf::Clock particleClock; //Clock for updating the particle system
	sf::Clock buttonClock; //Clock for button sound 
	int universalCounter = 0;
	int counter2 = 0;
	int counter3 = 0;
	int enemyX;
	int enemyY;
	int boss_apperance = 0;
	


	Gamerun();
	void run();
	Texture textureLoad(string filename);
	Font fontLoad(string filename);


};

#endif // ! __Gamerun__
