#ifndef GRIFFON_H
#define GRIFFON_H
#include <iostream>
#include "Creature.h"

class Griffon : public Creature
{
public:
	Griffon();
	~Griffon();

	//virtual int Attack();
	virtual int* Move(int x, int y, int m, int n);
};

#endif