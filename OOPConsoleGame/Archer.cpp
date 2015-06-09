#include "Archer.h"
#include <iostream>

Archer::Archer()
{
	this->setDamage(2);
	this->setDefense(1);
	this->setHealth(20);
	this->setMana(20);
	this->setStamina(3);

	this->setCritChance(5);
}

Archer::~Archer()
{
}

/*int Archer::Attack()
{

}*/

int* Archer::Move(int x, int y, int m, int n)
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