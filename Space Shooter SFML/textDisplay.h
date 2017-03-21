#pragma once

#ifndef __textDisplay__
#define __textDisplay__

#include "entity.h"


class textDisplay : public entity
{
public:

	//Variables
	float movementSpeed = 2.0;
	int counter = 0;
	bool destroy = false;
	int lifeTime = 25;
	string myString = "Default";

	textDisplay();
	void update();
	//void updateMovement();
};

#endif /*__textDisplay__*/
