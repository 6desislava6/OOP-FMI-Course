#include "Footman.h"
#include <iostream>

Footman::Footman()
{
	this->setDamage(3);
	this->setDefense(1);
	this->setHealth(25);
	this->setMana(25);
	this->setStamina(4);

	this->setCritChance(5);
}

Footman::~Footman()
{
}

/*int Footman::Attack()
{

}*/

int* Footman::Move(int x, int y, int m, int n)
{
	int result[2];
	result[0] = m;
	result[1] = n;
	double distance = sqrt(pow(m - x, 2) + pow(n - y, 2));
	if (distance <= this->getStamina())
	{
		return result;
	}
	else
	{
		while (distance > this->getStamina())
		{
			if (x < m && y < n)
			{
				m -= 1;
				n -= 1;
			}
			else if (x < m && y > n)
			{
				m -= 1;
				n += 1;
			}
			else if (x > m && y < n)
			{
				m += 1;
				n -= 1;
			}
			else if (x > m && y > n)
			{
				m += 1;
				n += 1;
			}
			else if (x == m && y < n)
			{
				n -= 1;
			}
			else if (x == m && y > n)
			{
				n += 1;
			}
			else if (x < m && y == n)
			{
				m -= 1;
			}
			else if (x > m && y == n)
			{
				m += 1;
			}

			distance = sqrt(pow(m - x, 2) + pow(n - y, 2));
		}
		result[0] = m;
		result[1] = n;
		return result;
	}
}