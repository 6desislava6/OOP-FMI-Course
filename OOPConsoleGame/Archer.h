#ifndef ARCHER_H
#define ARCHER_H
#include <iostream>
#include "Creature.h"

class Archer : public Creature
{
public:
	Archer();
	~Archer();

	//virtual int Attack();
	virtual int* Move(int x, int y, int m, int n);
};

#endif