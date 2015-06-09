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
	cout << "You are in the MAIN MENU." << endl;
	cout << "Make your choice:" << endl
		<< "start -> start new game" << endl
		<< "shop -> go to the shop" << endl
		<< "exit -> exit the game" << endl;

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
	// GameMenu ������������ �������� ����� �� �������� �� ������ �� ����� � ����������,
	// ������ ����������� �� ������ n (no).
	// ����� � ����� �� �����, ����� �� ����������.
	// ���� ���� ��� ������ ���� �� �������, �� �� ����� ��� ���� �� �� �����.
	// ����� �� ���������� � ���������� � ��������� ��������.

	while (true)
	{
		cout << "GAME MENU" << endl;
		cout << "Continue? y/n";

		// �������� ���� ������������ ���������� ����.
		string userInput;
		vector<string> input;
		getline(cin, userInput);
		input = this->splitUserInput(userInput);

		// ��� ������������ �� ������, ������� �� ����������.
		if (input.at(0) == "n")
		{
			return;
		}
		else
		{
			//������ ���������� � 2 ����: �� ����� � ����������.
			this->PlayersTurn();
			this->EnemysTurn();
		}
		// TODO: ��� ����� � �����.
	}
}
// ����, ���� ����� ������������ ���� �� �� �������� �����.
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

//��������� ����� �� �����������.
vector<string> Game::splitUserInput(const string& s)
{
	stringstream ss(s);

	istream_iterator<string> it(ss);
	istream_iterator<string> end;
	vector<string> tokens(it, end);

	return tokens;
}

// Engine: ���� ������ �� ������.
void Game::Run()
{
	this->mainMenu();
}

// ��������� �������� �� ������������, ������ �������� �����.
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

// �������� ������� � ��������.
void Game::PrintItems()
{
	cout << "Peasant: " << this->getShop()->getItems()["Peasant"] << " gold" << endl
		<< "Footman: " << this->getShop()->getItems()["Footman"] << " gold" << endl
		<< "Archer: " << this->getShop()->getItems()["Archer"] << " gold" << endl
		<< "Griffon: " << this->getShop()->getItems()["Griffon"] << " gold" << endl;
}

// ��������� �������� �� ����.
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

	// ����������� ���� �������� ���������� �� �� �������� �� �����.
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

//��������� �������� �� �������.
// ���������:
// - �������� �����
// - �������� �����
// - ����������, ����� �� ���������
// - ����������, ����� �� ���������

void Game::MakeAttackLogic(Player* attackingPlayer, short typeCreatureAttacking, Player* attackedPlayer, short typeCreatureAttacked)
{
	// ������� ����� �� ����������
	int summ_attack = 0;
	vector<Creature*> attackingCreatures = (attackingPlayer->getCreaturesPossesed())[typeCreatureAttacking];
	vector<Creature*> attackedCreatures = (attackedPlayer->getCreaturesPossesed())[typeCreatureAttacked];

	for (size_t i = 0; i < attackingCreatures.size(); i++)
	{
		//����� �� ���������� ��� ������� �������.
		//���������� ����� �� ���������� �������� ���� -> �������� �����.
		summ_attack += attackingCreatures[i]->Attack();
	}
	// ����� �� ����� �����.
	int killed = summ_attack / attackedCreatures[0]->getDefense();
	// ���������� �������.
	attackedPlayer->RemoveCreature(killed, typeCreatureAttacked);
	cout << "You killed " << killed << " " << typeCreatureAttacked;

}

// ������ �����, � ���������� �� �������� �����.
void Game::MakeWholeAttack(vector<string> input)
{
	int source_x = atoi(input.at(1).c_str());
	int source_y = atoi(input.at(2).c_str());
	int dest_x = atoi(input.at(3).c_str());
	int dest_y = atoi(input.at(4).c_str());

	if (source_x < 0 || source_x >= MATRIX_X || source_y < 0 || source_y >= MATRIX_Y ||
		dest_x < 0 || dest_x >= MATRIX_X || dest_y < 0 || dest_y >= MATRIX_Y)
	{
		cout << "Invalid coords!" << endl;
	}
	//map �� char � int.
	//� �� destinantion-a ����
	char position = this->m_battlefield->getBattlefield(source_x, source_y);
	char destination = this->m_battlefield->getBattlefield(dest_x, dest_y);

	map<char, int> PtypeCreatures = { { PPeasantChar, 0 }, { PFootmanChar, 1 }, { PArcherChar, 2 }, { PGriffonChar, 3 } };
	map<char, int> EtypeCreatures = { { EPeasantChar, 0 }, { EFootmanChar, 1 }, { EArcherChar, 2 }, { EGriffonChar, 3 } };

	// ����������� ���� �������� ���������� �� �� �������� �� �����.
	if (PtypeCreatures.find(position) == PtypeCreatures.end()) {
		cout << "You have no creatures on this field!";
	}
	// ����������� ���� ����������� ���������� �� �� �������� �� ����������.
	else if (EtypeCreatures.find(destination) == EtypeCreatures.end()){
		cout << position;
		cout << "There is no enemy!";
	}
	// ��� ������ � �����, ���������.
	else {
		this->MakeAttackLogic(m_player, PtypeCreatures[position], m_enemy, EtypeCreatures[destination]);
	}
	// �������� ��������� ����.
	this->m_battlefield->printBattlefield();
}

//���� ��� ��� �� ������� �� �����.
void Game::PlayersTurn(){
	cout << "It is YOUR turn!" << endl;
	cout << "Make your choice:" << endl
		<< "move x y m n (x, y: <source coords>; m, n: <destination coords>)" << endl
		<< "attack x y m n (x, y: <source coords>; m, n: <destination coords>" << endl
		<< "exit -> Finish turn without making anything" << endl;

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

	else if (input.at(0) == "exit")
	{
		return;
	}
	else
	{
		cout << "Invalid command!" << endl;
	}

	cout << "Finished Player's turn!" << endl;
}
void Game::EnemysTurn(){
	srand(time(nullptr));
	// ��������, ����� �� ��������, � ����� �� ������� �����������, � � rand()
	int index = rand() % m_enemy->getCreaturesPossesed().size();

	// ������ �� ����������, � ����� �� ������� �����������, ������� �� ������� �������.
	auto enemyCreatures = m_enemy->getCreaturesPossesed()[index];
	
	int* enemyCreaturesCoords = nullptr;
	switch (index)
	{
		case 0: enemyCreaturesCoords = m_battlefield->getEnemyPeasantCoords(); break;
		case 1: enemyCreaturesCoords = m_battlefield->getEnemyFootmanCoords(); break;
		case 2: enemyCreaturesCoords = m_battlefield->getEnemyArcherCoords(); break;
		case 3: enemyCreaturesCoords = m_battlefield->getEnemyGriffonCoords(); break;
	}

	// �������� ��� �������� �� ���-����� �� ����, � ����� �� ������� �����������.
	int indexClosest = this->WhichIsClosest(enemyCreaturesCoords,
		m_battlefield->getPlayerPeasantCoords(),
		m_battlefield->getPlayerFootmanCoords(),
		m_battlefield->getPlayerArcherCoords(),
		m_battlefield->getPlayerGriffonCoords());

	cout << "HE ATTACKS!" << endl;
	this->MakeAttackLogic(m_enemy, index, m_player, indexClosest);
}

int Game::WhichIsClosest(int* initialCoords, int* peasants, int* footmen, int* archers, int* griffons)
{
	
	map<int, int> CreaturesDistance = { { 0, this->CalculateDistance(initialCoords, peasants) },
	{ 1, this->CalculateDistance(initialCoords, footmen) },
	{ 2, this->CalculateDistance(initialCoords, archers) },
	{ 3, this->CalculateDistance(initialCoords, griffons) },
	};

	auto it = CreaturesDistance.begin();
	auto end = CreaturesDistance.end();

	float min_value = it->second;
	int index = it->first;
	for (; it != end; ++it) {
		if (it->second < min_value) {
			min_value = it->second;
			index = it->first;
		}
	}
	return index;
}

int Game::CalculateDistance(int* coords1, int* coords2)
{
	return int(sqrt((coords1[0] - coords2[0])*(coords1[0] - coords2[0])* +(coords1[1] - coords2[1])*(coords1[1] - coords2[1])));
}