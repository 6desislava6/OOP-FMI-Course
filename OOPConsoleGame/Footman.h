#ifndef FOOTMAN_H
#define FOOTMAN_H
#include <iostream>
#include "Creature.h"

class Footman : public Creature
{
public:
	Footman();
	~Footman();

	//virtual int Attack();
	virtual int* Move(int x, int y, int m, int n);
};

#endif