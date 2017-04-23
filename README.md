# 1st Year Comp Sci End-Of-Year Project

Space Shooter game made in C++
Uses SFML & Thor External Libraries

Credits to:
Alex McBean
N0696066

# Declaration of Ownership 

I, Alex McBean (N0696066) herby declare that am I the sole author of the associated report and software exclusive of the software declared below.

I am aware of the University’s rules on plagiarism and collusion and I understand that, if I am found to have broken these rules, it will be treated as Academic misconduct and dealt with accordingly.

I understand that I must submit this coursework by the time and date published.

I understand that it is up to me and me alone to ensure that I submit my full and complete coursework and that any missing elements submitted after the deadline will be disregarded.

I understand that the above rules apply even in the eventuality of computer or other information technology failures.

# Libraries used used
I have used the following from these sources:

[SFML](https://www.sfml-dev.org/)

[Thor](http://www.bromeon.ch/libraries/thor/)

# Code Sourced
The [random.cpp](https://github.com/Lucky38i/1st-Year-Comp-SCI-Project/blob/master/Space%20Shooter%20SFML/random.cpp) was entirely sourced from [here](https://youtu.be/owr_OBkE5Z4?t=43s)

```C++

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
```
This class base was used for AI movement and sprite selection and a few more things I can't thing of, however the functions and lines of code that made use of this class were of my own

