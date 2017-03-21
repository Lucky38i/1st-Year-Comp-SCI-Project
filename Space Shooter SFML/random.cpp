#include "random.h"
#include <stdlib.h>


int generateRandom(int max)
{
	int randomNumber = rand();
	float random = (randomNumber % max) + 1;
	int myRandom = random;
	return myRandom;
}

int generateRandom0(int max)
{
	int randomNumber = rand();
	float random = (randomNumber % max);
	int myRandom = random;
	return myRandom;
}

float generateRandomFloat(float lo, float hi)
{
	float myRandom = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));
	return myRandom;
}

bool generateRandomBool()
{
	int randomNumber = rand();
	float random = (randomNumber % 2) + 1;
	int myRandom = random;
	if (random == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}



