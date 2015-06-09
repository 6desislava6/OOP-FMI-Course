#ifndef HERO_H
#define HERO_H
#include <iostream>
#include "Creature.h"

class Hero : public Creature
{
public:
	Hero();
	~Hero();

	//virtual int Attack();
	virtual void Move();
};

#endif