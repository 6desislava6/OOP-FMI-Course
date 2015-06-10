	#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Shop.h"
#include "Battlefield.h"

class Game
{
private:
	Player* m_player = new Player("You");
	Player* m_enemy = new Player("Enemy");

	Shop* m_shop = new Shop();
	Battlefield* m_battlefield = new Battlefield();

	void MakeBuyLogic(string userInput, int numberOfCreaturesWanted);
	void MakeAttackLogic(Player*, short, Player*, short);
	void MakeMoveLogic(vector<string> input);
	void MakeWholeAttack(vector<string> input);
	void PlayersTurn();
	void EnemysTurn();
	void PrintItems();
	int CalculateDistance(int*, int*);
	void DeleteDead();
	Player* CheckSomebodyDied();

public:
	/// Връща индекс на най-близо намиращите се същества.
	int WhichIsClosest(int*, int*, int*, int*, int*);

	Game();
	~Game();

	Player* getCurrentEnemy() const;
	Player* getCurrentPlayer() const;
	Shop* getShop() const;

	void mainMenu();
	void shopMenu();
	void gameMenu();
	void Run();

	int saveBattlefield();
	int saveCreatureStats();
	vector<string> splitUserInput(const string& s);


};

#endif