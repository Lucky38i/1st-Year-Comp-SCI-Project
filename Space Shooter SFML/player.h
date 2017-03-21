#pragma once
#ifndef __player__
#define __player__

#include "entity.h"


class player: public entity
{
public:

	//Variables
	float movementSpeed = 5;
	int attackDamage = 1;
	int hp = 20;
	int score = 0;
	bool canMoveLeft = true;
	bool canMoveRight = true;

	//Constructors
	player();
	void update();
	void updateMovement();
};

#endif /* __player__ */

