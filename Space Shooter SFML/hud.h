#pragma once
#ifndef __hud__
#define __hud__

#include "entity.h"
#include "player.h"
#include "enemy.h"

class hud : public entity
{
public:

	//Variables

	//Fixed Varibales
	player player;
	enemy enemy;
	int health = player.hp;
	const int damage = enemy.attackDamage;
	int picWidth;
	int picHeight;
	int math;

	//Constructors
	hud();
	void update();
	void updateHealth();
};


#endif /* __hud__ */

