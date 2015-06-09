#include "Player.h"
#include "Creature.h"
#include "Peasant.h"
#include "Footman.h"
#include "Archer.h"
#include "Griffon.h"
#include "Hero.h"
#include <vector>

using namespace std;

Player::Player():
currentGold(STARTING_GOLD)
{	
	//1. Peasants, 2. Footmen, 3. Archers, 4. Griffons
	// Имаме вектор, от вектори, които съдържат съществата на героя.
	creaturesPossesed = { {  }, { }, { }, { } };
	this->addArcher(1);
	this->addPeasant(1);
	this->addFootman(1);
	this->addGriffon(1);

}

Player::~Player()
{
	auto pd = creaturesPossesed.begin();
	// Изтриваме всеки елемент, динамично заделен.
	// Първо обхождаме външния вектор, после вътрешния.
	for (pd = creaturesPossesed.begin(); pd != creaturesPossesed.end(); pd++)
	{
		auto innerIterator = pd->begin();
		for (innerIterator = pd->begin(); innerIterator != pd->end(); innerIterator++)
		{
			delete *innerIterator;
		}
	}

}

int Player::getCurrentGold() const
{
	return this->currentGold;
}

vector<vector<Creature*>> Player::getCreaturesPossesed() const
{
	return this->creaturesPossesed;
}

void Player::setCurrentGold(int amount)
{
	this->currentGold += amount;
}

void Player::addPeasant(int amount)
{	
	for (size_t i = 0; i < amount; i++)
	{
		this->creaturesPossesed[0].push_back(new Peasant());
	}
}

void Player::addFootman(int amount)
{
	for (size_t i = 0; i < amount; i++)
	{
		this->creaturesPossesed[1].push_back(new Footman());
	}
}

void Player::addArcher(int amount)
{
	for (size_t i = 0; i < amount; i++)
	{
		this->creaturesPossesed[2].push_back(new Archer());
	}
}

void Player::addGriffon(int amount)
{
	for (size_t i = 0; i < amount; i++)
	{
		this->creaturesPossesed[3].push_back(new Griffon());
	}
}
void Player::removePeasant(int amount)
{
	this->RemoveCreature(amount, 0);
}
void Player::RemoveCreature(int amount, short type)
{
	// Ако искаме да махнем повече, отколкото има, махаме всички.
	if (amount > creaturesPossesed[type].size())
	{
		amount = creaturesPossesed[type].size();
	}
	auto pd = this->creaturesPossesed[type].begin();
	for (size_t i = 0; i < amount; i++)
	{
		//Трием обекта, който е динамично заделен.
		delete *pd;
		// Сега го махаме от вектора.
		creaturesPossesed[type].erase(pd, pd + i);
	}
}