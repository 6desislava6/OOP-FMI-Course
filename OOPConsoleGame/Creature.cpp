#include "Creature.h"
#include <iostream>

using namespace std;

/// Конструктори
Creature::Creature():	damage(DAMAGE_STARTING), defense(DEFENSE_STARTING),
						health(HEALTH_STARTING), mana(MANA_STARTING),
						stamina(STAMINA_STARTING), critChance(CRITCHANCE_STARTING)
{
}

Creature::Creature(unsigned short damage,
	unsigned short defense,
	int stamina, int health,
	int mana, int critChance) : damage(damage), defense(defense),
health(health), mana(mana),
stamina(stamina), critChance(critChance)
{
}

/// Деструкторът съществува, макар и празен,
/// защото може да се override-не от свои наследници,
/// тъй като е базов клас.
Creature::~Creature()
{

}

/// Get-ери.
unsigned short Creature::getDamage() const
{
	return this->damage;
}

unsigned short Creature::getDefense() const
{
	return this->defense;
}

int Creature::getHealth() const
{
	return this->health;
}

int Creature::getMana() const
{
	return this->mana;
}

int Creature::getStamina() const
{
	return this->stamina;
}

int Creature::getCritChance() const
{
	return this->critChance;
}
/// Set-ери.
void Creature::setDamage(const unsigned short damage)
{
	this->damage = damage;
}

void Creature::setDefense(const unsigned short defense)
{
	this->defense = defense;
}

void Creature::setHealth(const int health)
{
	this->health = health;
}

void Creature::setMana(const int mana)
{
	this->mana = mana;
}

void Creature::setStamina(const int stamina)
{
	this->stamina = stamina;
}

void Creature::setCritChance(const int critChance)
{
	this->critChance = critChance;
}

/// Основни методи, които са чисто виртуални.
/// Когато атакува, маната му се намалява. Връща атака.
int Creature::Attack()
{
	if (this->mana >= this->damage)
	{
		this->mana -= this->damage;
		return this->damage;
	}
	else if (this->mana > 0)
	{
		int force = this->mana;
		this->mana = 0;
		return force;
	}
	else
	{
		return 0;
	}
}

int* Creature::Move(int x, int y, int m, int n)
{
	int result[2] = { m, n };
	return result;
}
