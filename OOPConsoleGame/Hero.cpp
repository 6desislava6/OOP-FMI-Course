#include "Hero.h"
#include <iostream>

Hero::Hero()
{
	this->setDamage(2);
	this->setDefense(2);
	this->setHealth(30);
	this->setMana(30);
	this->setStamina(0);

	this->setCritChance(5);
}

Hero::~Hero()
{
}

/*int Hero::Attack()
{

}*/

void Hero::Move()
{

}