#include "Game.h"
#include "Player.h"
#include "Peasant.h"
#include "Footman.h"
#include "Archer.h"
#include "Griffon.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>
#include <time.h>   
#include <fstream>
#include <iomanip>
using namespace std;

Game::Game()
{
	this->m_enemy->addPeasant(2);
	this->m_enemy->addFootman(2);
	this->m_enemy->addArcher(1);
	this->m_enemy->addGriffon(1);
}

Game::~Game()
{
	delete this->m_player;
	delete this->m_enemy;
	delete this->m_shop;
	delete this->m_battlefield;
}

Player* Game::getCurrentEnemy() const
{
	return this->m_enemy;
}

Player* Game::getCurrentPlayer() const
{
	return this->m_player;
}

Shop* Game::getShop() const
{
	return this->m_shop;
}

void Game::mainMenu()
{
	string userInput;
	cout << "MAIN MENU." << endl;
	cout << "start" << endl
		<< "shop" << endl
		<< "exit" << endl;

	while (cin)
	{
		getline(cin, userInput);

		if (userInput == "start")
		{
			this->gameMenu();
		}
		else if (userInput == "shop")
		{
			this->shopMenu();
		}
		else if (userInput == "exit")
		{
			cout << "Bye Bye" << endl;
			break;
		}
		else
		{
			cout << "Invalid command!" << endl;
		}

		cout << "Please make your choice!" << endl;
	}
}

void Game::gameMenu()
{
	/// GameMenu ������������ �������� ����� �� �������� �� ������ �� ����� � ����������,
	/// ������ ����������� �� ������ n (no).
	/// ����� � ����� �� �����, ����� �� ����������.
	/// ���� ���� ��� ������ ���� �� �������, �� �� ����� ��� ���� �� �� �����.
	/// ����� �� ���������� � ���������� � ��������� ��������.

	while (true)
	{
		cout << "GAME MENU" << endl;
		cout << "Continue? y/n";

		/// �������� ���� ������������ ���������� ����.
		string userInput;
		vector<string> input;
		getline(cin, userInput);
		input = this->splitUserInput(userInput);

		/// ��� ������������ �� ������, ������� �� ����������.
		if (input.at(0) == "n")
		{
			return;
		}
		else
		{
			///������ ���������� � 2 ����: �� ����� � ����������.
			this->PlayersTurn();
			this->EnemysTurn();
			/// ��������� �� �������� �������� � �� ������� �� ������.
			this->DeleteDead();
			/// ��������� ���� � ������� ����� �� ��������.
			Player* died = this->CheckSomebodyDied();
			if (died)
			{
				if (died->GetName() == "You")
				{
					cout << "You LOST. You lose 100 Gold" << endl;
					m_player->setCurrentGold(-100);
					return;
				}
				else if (died->GetName() == "Enemy")
				{
					cout << "You WON. You win 200 Gold" << endl;
					m_player->setCurrentGold(200);
					return;
				}
			}
			this->saveBattlefield();
			this->saveCreatureStats();
		}
	}
}
//// ����, ���� ����� ������������ ���� �� �� �������� �����.
void Game::shopMenu()
{
	cout << "SHOP MENU" << endl;
	cout << "Make your choice:" << endl
		<< "items -> items available in the shop" << endl
		<< "buy <item_name> <amount> -> buy new item(s)" << endl
		<< "gold -> the amount of gold you possess" << endl
		<< "exit -> go to the MAIN MENU" << endl;

	string userInput;
	vector<string> input;

	while (true)
	{
		getline(cin, userInput);
		input = this->splitUserInput(userInput);

		if (input.at(0) == "items")
		{
			this->PrintItems();
		}
		else if (input.at(0) == "buy")
		{
			string userInput = input.at(1);
			int numberOfCreaturesWanted = atoi(input.at(2).c_str());
			this->MakeBuyLogic(userInput, numberOfCreaturesWanted);
		}
		else if (input.at(0) == "gold")
		{
			cout << this->getCurrentPlayer()->getCurrentGold() << endl;
		}
		else if (input.at(0) == "exit")
		{
			break;
		}
		else
		{
			cout << "Invalid command!" << endl;
		}

		cout << "Please make your choice." << endl;
	}
}

///��������� ����� �� �����������.
vector<string> Game::splitUserInput(const string& s)
{
	stringstream ss(s);

	istream_iterator<string> it(ss);
	istream_iterator<string> end;
	vector<string> tokens(it, end);

	return tokens;
}

/// Engine: ���� ������ �� ������.
void Game::Run()
{
	this->mainMenu();
}

/// ��������� �������� �� ������������, ������ �������� �����.
void Game::MakeBuyLogic(string userInput, int numberOfCreaturesWanted)
{
	int creatureValue = (this->getShop()->getItems())[userInput];

	int cost = creatureValue * numberOfCreaturesWanted;

	if (cost > this->getCurrentPlayer()->getCurrentGold())
	{
		cout << "Not enough gold!" << endl;
	}
	else
	{	
		this->getCurrentPlayer()->addPeasant(numberOfCreaturesWanted);
		this->getCurrentPlayer()->setCurrentGold(-cost);
		cout << "Bought " << userInput << " for " << cost<< endl;
	}
}

/// �������� ������� � ��������.
void Game::PrintItems()
{
	cout << "Peasant: " << this->getShop()->getItems()["Peasant"] << " gold" << endl
		<< "Footman: " << this->getShop()->getItems()["Footman"] << " gold" << endl
		<< "Archer: " << this->getShop()->getItems()["Archer"] << " gold" << endl
		<< "Griffon: " << this->getShop()->getItems()["Griffon"] << " gold" << endl;
}

/// ��������� �������� �� ����.
void Game::MakeMoveLogic(vector<string> input)
{

	int source_x = atoi(input.at(1).c_str());
	int source_y = atoi(input.at(2).c_str());
	int dest_x = atoi(input.at(3).c_str());
	int dest_y = atoi(input.at(4).c_str());
	map<const char, Creature*> creatures;
	creatures.insert(std::make_pair(PPeasantChar, new Peasant()));
	creatures.insert(std::make_pair(PFootmanChar, new Footman()));
	creatures.insert(std::make_pair(PArcherChar, new Archer()));
	creatures.insert(std::make_pair(PGriffonChar, new Griffon()));

	creatures.insert(std::make_pair(EPeasantChar, new Peasant()));
	creatures.insert(std::make_pair(EFootmanChar, new Footman()));
	creatures.insert(std::make_pair(EArcherChar, new Archer()));
	creatures.insert(std::make_pair(EGriffonChar, new Griffon()));

	map<char, int> PtypeCreatures = { { PPeasantChar, 0 }, { PFootmanChar, 1 }, { PArcherChar, 2 }, { PGriffonChar, 3 } };
	char position = this->m_battlefield->getBattlefield(source_x, source_y);

	/// ����������� ���� �������� ���������� �� �� �������� �� �����.
	if (PtypeCreatures.find(position) == PtypeCreatures.end()) {
		cout << "You have no creatures on this field! You cant move them"<< endl;
		return;
	}
	if (source_x < 0 || source_x >= MATRIX_X || source_y < 0 || source_y >= MATRIX_Y ||
		dest_x < 0 || dest_x >= MATRIX_X || dest_y < 0 || dest_y >= MATRIX_Y)
	{
		cout << "Invalid coords! Out of range!" << endl;
	}

	else
	{
		if (this->m_battlefield->getBattlefield(dest_x, dest_y) == BATTLEFIELD_SPACE)
		{
			char creatureChar = this->m_battlefield->getBattlefield(source_x, source_y);
			Creature* creature = creatures[creatureChar];
			int m = creature->Move(source_x, source_y, dest_x, dest_y)[0];
			int n = creature->Move(source_x, source_y, dest_x, dest_y)[1];
			this->m_battlefield->setCreatureCoords(m, n, creatureChar);
			cout << "You have moved to: " << m <<", "<< n <<endl;
		}
		else
		{
			cout << "Move forbidden!" << endl;
		}
	}
	this->m_battlefield->printBattlefield();
}

///��������� �������� �� �������.
/// ���������:
/// - �������� �����
/// - �������� �����
/// - ����������, ����� �� ���������
/// - ����������, ����� �� ���������

/// ��������� �������� �� �������.
/// ������ �� �������� �����, �������� �����, � ����� �������� �� ������� � ����� �������� �� �������.
void Game::MakeAttackLogic(Player* attackingPlayer, short typeCreatureAttacking, Player* attackedPlayer, short typeCreatureAttacked)
{	
	map<int, string> names = { { 0, "Peasants" }, { 1, "Footmen" }, { 2, "Archers" }, { 3, "Griffons" }, };
	/// ������� ����� �� ����������
	int summ_attack = 0;
	vector<Creature*> attackingCreatures = (attackingPlayer->getCreaturesPossesed())[typeCreatureAttacking];
	vector<Creature*> attackedCreatures = (attackedPlayer->getCreaturesPossesed())[typeCreatureAttacked];

	for (size_t i = 0; i < attackingCreatures.size(); i++)
	{
		///����� �� ���������� ��� ������� �������.
		///���������� ����� �� ���������� �������� ���� -> �������� �����.
		summ_attack += attackingCreatures[i]->Attack();
	}
	/// ����� �� ����� �����.
	int killed = summ_attack / attackedCreatures[0]->getDefense();
	/// ���������� �������.
	killed = attackedPlayer->RemoveCreature(killed, typeCreatureAttacked);
	this->DeleteDead();
	cout << attackingPlayer->GetName() << " killed " << killed << " " << names[typeCreatureAttacked] << endl;

}

/// ������ �����, � ���������� �� �������� �����.
void Game::MakeWholeAttack(vector<string> input)
{
	int source_x = atoi(input.at(1).c_str());
	int source_y = atoi(input.at(2).c_str());
	int dest_x = atoi(input.at(3).c_str());
	int dest_y = atoi(input.at(4).c_str());

	int playerCoords[2] = { source_x, source_y };
	int enemyCoords[2] = { dest_x, dest_y };


	if (source_x < 0 || source_x >= MATRIX_X || source_y < 0 || source_y >= MATRIX_Y ||
		dest_x < 0 || dest_x >= MATRIX_X || dest_y < 0 || dest_y >= MATRIX_Y)
	{
		cout << "Invalid coords!" << endl;
	}
	///map �� char � int.
	///� �� destinantion-a ����
	char position = this->m_battlefield->getBattlefield(source_x, source_y);
	char destination = this->m_battlefield->getBattlefield(dest_x, dest_y);

	map<char, int> PtypeCreatures = { { PPeasantChar, 0 }, { PFootmanChar, 1 }, { PArcherChar, 2 }, { PGriffonChar, 3 } };
	map<char, int> EtypeCreatures = { { EPeasantChar, 0 }, { EFootmanChar, 1 }, { EArcherChar, 2 }, { EGriffonChar, 3 } };

	/// ����������� ���� �������� ���������� �� �� �������� �� �����.
	if (PtypeCreatures.find(position) == PtypeCreatures.end()) {
		cout << "You have no creatures on this field!";
	}
	/// ����������� ���� ����������� ���������� �� �� �������� �� ����������.
	else if (EtypeCreatures.find(destination) == EtypeCreatures.end()){
		cout << position;
		cout << "There is no enemy!";
	}

	/// ��� ��������� �� � ������ �� ������������ ����� ����������� � �����������, ����� ���� �� �� ���������, �� ����� �� ���������.
	else if (CalculateDistance(playerCoords, enemyCoords) > m_player->getCreaturesPossesed()[PtypeCreatures[position]].at(0)->getStamina())
	{
		Creature* creature = m_player->getCreaturesPossesed()[PtypeCreatures[position]].at(0);
		int m = creature->Move(source_x, source_y, dest_x, dest_y)[0];
		int n = creature->Move(source_x, source_y, dest_x, dest_y)[1];
		/// ��������� ������������ �� ����������.
		this->m_battlefield->setCreatureCoords(m, n, position);
		cout << "You have moved to: " << m << ", " << n << endl;
	}
	/// ��� ������ � �����, ���������.
	else {
		this->MakeAttackLogic(m_player, PtypeCreatures[position], m_enemy, EtypeCreatures[destination]);
	}
	/// �������� ��������� ����.
	this->m_battlefield->printBattlefield();
}

///���� ��� ��� �� ������� �� �����.
void Game::PlayersTurn(){
	cout << "It is YOUR turn!" << endl;
	cout << "Make your choice:" << endl
		<< "move x y m n (x, y: <source coords>; m, n: <destination coords>)" << endl
		<< "attack x y m n (x, y: <source coords>; m, n: <destination coords>" << endl
		<< "pass -> Finish turn without making anything" << endl;

	string userInput;
	vector<string> input;

	this->m_battlefield->printBattlefield();

	getline(cin, userInput);
	input = this->splitUserInput(userInput);

	if (input.at(0) == "move")
	{
		this->MakeMoveLogic(input);
	}

	else if (input.at(0) == "attack")
	{
		this->MakeWholeAttack(input);
	}

	else if (input.at(0) == "pass")
	{
		return;
	}
	else
	{
		cout << "Invalid command!" << endl;
	}

	cout << "Finished Player's turn!" << endl;
}

/// ������� ������������ �� ���� �� ����������.
/// ������� ������ ��� �� ����� ������ ������.
void Game::EnemysTurn(){
	srand(time(nullptr));
	/// ��������, ����� �� ��������, � ����� �� ������� �����������, � � rand()
	int index = rand() % m_enemy->getCreaturesPossesed().size();

	/// ������ �� ����������, � ����� �� ������� �����������, ������� �� ������� �������.
	auto enemyCreatures = m_enemy->getCreaturesPossesed()[index];
	/// ��� ��������� �������� �� ���� (���� �� ���� ��), ������ ���, ������ �� ������� �� ������������.
	while (m_enemy->getCreaturesPossesed()[index].size() == 0)
	{
		index = rand() % m_enemy->getCreaturesPossesed().size();
		enemyCreatures = m_enemy->getCreaturesPossesed()[index];
	}

	int* enemyCreaturesCoords = nullptr;
	switch (index)
	{
		case 0: enemyCreaturesCoords = m_battlefield->getEnemyPeasantCoords(); break;
		case 1: enemyCreaturesCoords = m_battlefield->getEnemyFootmanCoords(); break;
		case 2: enemyCreaturesCoords = m_battlefield->getEnemyArcherCoords(); break;
		case 3: enemyCreaturesCoords = m_battlefield->getEnemyGriffonCoords(); break;
	}
	/// ���������� �� ���������� �� �����.
	vector<int*> coords = { m_battlefield->getPlayerPeasantCoords(),
		m_battlefield->getPlayerFootmanCoords(),
		m_battlefield->getPlayerArcherCoords(),
		m_battlefield->getPlayerGriffonCoords() };

	/// �������� ��� �������� �� ���-����� �� ����, � ����� �� ������� �����������.
	int indexClosest = this->WhichIsClosest(enemyCreaturesCoords,
											coords[0],
											coords[1],
											coords[2],
											coords[3]);

	///��������� ���� � ���������� ������, ��� � � ������� ��������� �� ���������� -> �������.
	/// ��� �� �, ����� ��.
	if (CalculateDistance(coords[indexClosest], enemyCreaturesCoords) > enemyCreatures.front()->getStamina())
	{
		Creature* creature = enemyCreatures.at(0);
		int m = creature->Move(enemyCreaturesCoords[0],
							   enemyCreaturesCoords[1],
							   coords[indexClosest][0],
							   coords[indexClosest][1])[0];

		int n = creature->Move(enemyCreaturesCoords[0],
							   enemyCreaturesCoords[1],
							   coords[indexClosest][0],
							   coords[indexClosest][1])[1];

		/// ��������� ������������ �� ����������.
		map<int, char> EtypeCreatures = { { 0, EPeasantChar }, { 1, EFootmanChar }, { 2, EArcherChar }, { 3, EGriffonChar} };

		this->m_battlefield->setCreatureCoords(m, n, EtypeCreatures[index]);
		cout << "Enemy has moved to: " << m << ", " << n << endl;
	}
	else {
		/// ��� ��� ���������� �����, ����������� �������.
		this->MakeAttackLogic(m_enemy, index, m_player, indexClosest);
	}
	this->m_battlefield->printBattlefield();


}

/// ��������� ��� �������� �� ���-����� �� ������ ����������
int Game::WhichIsClosest(int* initialCoords, int* peasants, int* footmen, int* archers, int* griffons)
{
	
	map<int, int> CreaturesDistance = { { 0, this->CalculateDistance(initialCoords, peasants) },
	{ 1, this->CalculateDistance(initialCoords, footmen) },
	{ 2, this->CalculateDistance(initialCoords, archers) },
	{ 3, this->CalculateDistance(initialCoords, griffons) },
	};

	auto it = CreaturesDistance.begin();
	auto end = CreaturesDistance.end();

	int min_value = it->second;
	int index = it->first;
	for (; it != end; ++it) {
		if (it->second < min_value) {
			min_value = it->second;
			index = it->first;
		}
	}
	/// ����� ������� �� ���-�������� ��������.
	return index;
}

/// ����� ���������� ����� ��� ����� � ������� �� ������������ ��.
int Game::CalculateDistance(int* coords1, int* coords2)
{
	/// ����������� ���� �������� ���������� �� ����� ������ - �.�.
	/// ������������ �� ���������� �� -1 -1, ������ �� ����� :D
	if (coords1 < 0 || coords2 < 0)
	{
		/// ��� �� - ������������ �� ��� � ����������.
		return std::numeric_limits<int>::max();
	}
	/// � �������� ������ ������ ������� ������������ � ���������� �������.
	return int(sqrt((coords1[0] - coords2[0])*(coords1[0] - coords2[0])* +(coords1[1] - coords2[1])*(coords1[1] - coords2[1])));
}


/// ������� �������� �������� �� ������ :D
/// ����� ������������ �� -1, -1, ������ ���� �� �����������.
/// ������� �� � �� �������.
void Game::DeleteDead()
{
	vector<vector<Creature*>> playerCreatures = m_player->getCreaturesPossesed();
	vector<vector<Creature*>> enemyCreatures = m_enemy->getCreaturesPossesed();

	/// ������� ���������� �� ����� � ��������� ���� ��� ������, ����� �������� �� 0 �� ����.
	/// � ����� ������ ���� �������� �� �������� �� �������.
	auto pd = playerCreatures.begin();
	int counter = 0;

	for (auto &i : playerCreatures) {
		if (i.size() == 0)
		{
			int x;
			int y;
			switch (counter)
			{
			case 0:
				x = m_battlefield->getPlayerPeasantCoords()[0];
				y = m_battlefield->getPlayerPeasantCoords()[1];
				m_battlefield->setPlayerPeasantCoords(-1, -1);
				break;

			case 1:
				x = m_battlefield->getPlayerFootmanCoords()[0];
				y = m_battlefield->getPlayerFootmanCoords()[1];
				m_battlefield->setPlayerFootmanCoords(-1, -1);
				break;

			case 2:
				x = m_battlefield->getPlayerArcherCoords()[0];
				y = m_battlefield->getPlayerArcherCoords()[1];
				m_battlefield->setPlayerArcherCoords(-1, -1);
				break;

			case 3:
				x = m_battlefield->getPlayerGriffonCoords()[0];
				y = m_battlefield->getPlayerGriffonCoords()[1];
				m_battlefield->setPlayerGriffonCoords(-1, -1);
				break;
			}
			m_battlefield->deleteCreatures(x, y);
		}
		counter++;
	}
	/// ������� ���������� �� ���������� � ��������� ���� ��� ������, ����� �������� �� 0 �� ����.
	/// � ����� ������ ���� �������� �� �������� �� �������.
	pd = enemyCreatures.begin();
	counter = 0;

	for (auto &i : enemyCreatures) {
		if (i.size() == 0)
		{
			int x;
			int y;
			switch (counter)
			{
			case 0:
				x = m_battlefield->getEnemyPeasantCoords()[0];
				y = m_battlefield->getEnemyPeasantCoords()[1];
				m_battlefield->setEnemyPeasantCoords(-1, -1);
				break;

			case 1:
				x = m_battlefield->getEnemyFootmanCoords()[0];
				y = m_battlefield->getEnemyFootmanCoords()[1];
				m_battlefield->setEnemyFootmanCoords(-1, -1);
				break;

			case 2:
				x = m_battlefield->getEnemyArcherCoords()[0];
				y = m_battlefield->getEnemyArcherCoords()[1];
				m_battlefield->setEnemyArcherCoords(-1, -1);
				break;

			case 3:
				x = m_battlefield->getEnemyGriffonCoords()[0];
				y = m_battlefield->getEnemyGriffonCoords()[1];
				m_battlefield->setEnemyGriffonCoords(-1, -1);
				break;
			}
			m_battlefield->deleteCreatures(x, y);
		}
		counter++;
	}
		
}

/// ����� ��� � �����... ��� nullptr
Player* Game::CheckSomebodyDied()
{
	/// ��� ��� ���� 1 ��������, ����� ������ � ���� �� ���� -> ����������� ����� � ���.
	vector<vector<Creature*>> playerCreatures = m_player->getCreaturesPossesed();
	vector<vector<Creature*>> enemyCreatures = m_enemy->getCreaturesPossesed();
	bool smbDied = true;

	for (auto &i : playerCreatures) {
		if (i.size() != 0)
		{
			smbDied = false;
		}
	}
	/// ��� smdDied �� � ������� false, ����� Player e �����
	if (smbDied)
	{
		return m_player;
	}

	for (auto &i : enemyCreatures) {
		if (i.size() != 0)
		{
			smbDied = false;
		}
	}

	/// ��� smdDied �� � ������� false, ����� ����������� e �����
	if (smbDied)
	{
		return m_enemy;
	}
	/// ����� ����� �� � �����.
	else {
		return nullptr;
	}
}

///������ � �������!

///������� ������ ��� ����.
int Game::saveBattlefield()
{
	ofstream myfile("battlefield.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < MATRIX_X; ++i)
		{
			for (int j = 0; j < MATRIX_Y; ++j)
			{
				myfile << setw(2) << this->m_battlefield->getBattlefield(i, j);
			}
			myfile << endl;
		}
	}
	else
		cout << "Unable to open file" << endl;
	return 0;
}

///������� ��������� �� ����������.
int Game::saveCreatureStats()
{
	ofstream myfile("creature_stats.txt");
	if (myfile.is_open())
	{
		myfile << PPeasantChar << " " << this->m_player->getCreaturesPossesed()[0].size() << endl;
		myfile << PArcherChar << " " << this->m_player->getCreaturesPossesed()[1].size() << endl;
		myfile << PFootmanChar << " " << this->m_player->getCreaturesPossesed()[2].size() << endl;
		myfile << PGriffonChar << " " << this->m_player->getCreaturesPossesed()[3].size() << endl;
		myfile << "H 1" << endl;
		myfile << EPeasantChar << " " << this->m_enemy->getCreaturesPossesed()[0].size() << endl;
		myfile << EArcherChar << " " << this->m_enemy->getCreaturesPossesed()[1].size() << endl;
		myfile << EFootmanChar << " " << this->m_enemy->getCreaturesPossesed()[2].size() << endl;
		myfile << EGriffonChar << " " << this->m_enemy->getCreaturesPossesed()[3].size() << endl;
		myfile << "EH 1" << endl;
		myfile.close();
	}
	else
		cout << "Unable to open file" << endl;
	return 0;
}
