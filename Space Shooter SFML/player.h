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
	unsigned int hp = 20;
	int score = 0;
	bool canMoveLeft = true;
	bool canMoveRight = true;
	bool powerUp_Triple = false;
	bool powerUp_FireRate = false;

	//Constructors
	player();
	void update();
	void updateMovement();
	void wallCollision(const int max_width, int dimension);
};

#endif /* __player__ */

