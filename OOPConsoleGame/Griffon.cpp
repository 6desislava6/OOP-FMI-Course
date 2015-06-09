#include "Griffon.h"
#include <iostream>

Griffon::Griffon()
{
	this->setDamage(4);
	this->setDefense(2);
	this->setHealth(30);
	this->setMana(30);
	this->setStamina(5);

	this->setCritChance(5);
}

Griffon::~Griffon()
{
}

/*int Griffon::Attack()
{

}*/

int* Griffon::Move(int x, int y, int m, int n)
{
	int* result = new int[2];
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