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

	//Fixed Variables
	int direction = 0; // 1 - left, 2 - right
	int counter = 0;
	int counterLife = 0;

	bool alive = true;


	enemy();
	void update();
	void updateMovement();
	void wallCollision();
};

#endif __enemy__

