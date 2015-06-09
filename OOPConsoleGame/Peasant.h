#ifndef PEASANT_H
#define PEASANT_H
#include <iostream>
#include "Creature.h"

class Peasant : public Creature
{
public:
	Peasant();
	~Peasant();

	//virtual int Attack();
	virtual int* Move(int x, int y, int m, int n);
};

#endif