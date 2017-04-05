#pragma once
#ifndef __enemy__
#define __enemy__

#include "entity.h"

class enemy: public entity
{
public:
	//Variables
	float movementSpeed = 1;
	float downSpeed = 0.5;
	int movementLength = 100;
	int attackDamage = 2;
	int hp = 3;
	int lifeTime = 1000;
	int deathValue = 10;
	double enemySpawnRate = 0.5; //Lower = faster eg. 1.5 = spawn enemy every 1.5 seconds

	//Fixed Variables
	int direction = 0; // 1 - left, 2 - right
	int counter = 0;
	int counterLife = 0;
	bool canMoveLeft = true;
	bool canMoveRight = true;

	bool alive = true;


	enemy();
	void update();
	void updateMovement();
	void wallCollision(const int max_width, int dimensions);
};

#endif __enemy__

