#pragma once
#ifndef __Particles__
#define __Particles__

#include <stdio.h>
#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>
#include <xtgmath.h>
#include <vector>
#include <functional>
#include <iostream>
#include <list>

#include <Thor/Particles.hpp>
#include <Thor/Animations.hpp>
#include <Thor/Vectors/PolarVector2.hpp>
#include <Thor/Math/Distributions.hpp>
#include <SFML/Graphics.hpp>

#pragma warning(disable:C4305)
class Particles
{
public:

	//Variables
	float fadeIn = 0.1;
	float fadeOut = 0.1;
	float rate = 15;
	float lifeTime = 20;

	//Fixed Variables
	thor::ParticleSystem system;
	thor::UniversalEmitter emitter;
	thor::PolarVector2f velocity;
	

	Particles();
	void update();

private:
protected:

};

#endif /* __Particles__ */
