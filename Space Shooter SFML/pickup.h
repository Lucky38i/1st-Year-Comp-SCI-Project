#pragma once
#ifndef __pickup__
#define __pickup__

#include "entity.h"

class pickup : public entity
{
public:

	//Variables
	bool isCoin = false;
	bool isPowerup_Triple = false;
	bool isPowerup_Fast = false;
	int counter = 0;
	bool destroy = false;
	int coinValue = 100;
	float dropSpeed = 2;

	pickup();
	void update();
	void animate();
};

#endif /* __pickup__ */
