#pragma once
#ifndef __random__
#define __random__

#include <stdio.h>
#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>
#include <xtgmath.h>
#include <vector>
#include <functional>
#include <ctime>
#include <stdlib.h>

#include <SFML\Main.hpp>
#include <SFML\Config.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <list>

using namespace std;

int generateRandom(int max);
int generateRandom0(int max);
float generateRandomFloat(float lo, float hi);
bool generateRandomBool();

#endif /* defined(__random__) */

