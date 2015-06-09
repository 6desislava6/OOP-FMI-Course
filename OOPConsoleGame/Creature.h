#ifndef CREATURE_H
#define CREATURE_H
#include <iostream>

class Creature
{
private:
	//// Статични променливи за класа.
	/// Нещо като стойности по подразбиране.
	static const unsigned short HEALTH_STARTING = 100;
	static const unsigned short DAMAGE_STARTING = 100;
	static const int DEFENSE_STARTING = 100;
	static const int MANA_STARTING = 100;
	static const int STAMINA_STARTING = 100;
	static const int CRITCHANCE_STARTING = 100;

	/// Това са нужните полета за героя.
	unsigned short damage;
	unsigned short defense;
	int health;
	int mana;
	int stamina;
	int critChance;

public:
	/// Конструктор по подразбиране
	Creature();

	/// Конструктор
	Creature(unsigned short damage,
			 unsigned short defense,
			 int stamina, int health, 
			 int mana, int critChance);

	/// Copy-конструктор
	Creature(const Creature&);

	/// Деструктор
	virtual ~Creature();

	/// Get-ери, които "обещават", че няма да променят инстанцията на класа,
	/// с думичката const.
	unsigned short getDamage() const;
	unsigned short getDefense() const;
	int getHealth() const;
	int getMana() const;
	int getStamina() const;
	int getCritChance() const;
	
	/// Set-ери.
	void setDamage(const unsigned short damage);
	void setDefense(const unsigned short defense);
	void setHealth(const int health);
	void setMana(const int mana);
	void setStamina(const int stamina);
	void setCritChance(const int critChance);

	virtual int Attack();
	virtual int* Move(int x, int y, int m, int n);


};



#endif