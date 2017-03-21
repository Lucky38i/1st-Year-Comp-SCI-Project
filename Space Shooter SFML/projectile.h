#ifndef __projectile__
#define __projectile__

#include "entity.h"

class projectile : public entity
{
public:
	//Variables
	float movementSpeed = 5;
	int attackDamage = 1;
	int lifeTime = 200;

	//Fixed Variables
	int direction = 1; // 1-up, 2-down, 3-left, 4-right
	bool destroy = false;
	int counterLife = 0;
	int counterAnimation = 0;

	projectile();
	void update();
	void updateAnimation();
	//void updateMovement();
};


#endif __projectile__
