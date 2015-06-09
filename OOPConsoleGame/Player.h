#ifndef PLAYER_H
#define PLAYER_H
#include "Creature.h"
#include <vector>

using namespace std;

class Player
{
private:
	static const int STARTING_GOLD = 300;
	int currentGold;
	string name;

public:
	vector<vector<Creature*>> creaturesPossesed;

	Player();
	///��� �� ���, ����� ��� ������.
	Player(string name);

	Player(const Player&);

	~Player();

	int getCurrentGold() const;
	void setCurrentGold(int amount);

	///TODO:
	/// getter �� ����������.

	vector<vector<Creature*>>  getCreaturesPossesed() const;


	void addPeasant(int amount);
	void addFootman(int amount);
	void addArcher(int amount);
	void addGriffon(int amount);

	int RemoveCreature(int, short);

	void removePeasant(int amount);
	///void removeFootman(int amount);
	///void removeArcher(int amount);
	///void removeGriffon(int amount);
	string GetName();
};

#endif