#include "Creature.h"
#include "Peasant.h"
#include "Footman.h"
#include "Archer.h"
#include "Griffon.h"
#include "Hero.h"
#include "Player.h"
#include "Shop.h"
#include "Game.h"
#include "Battlefield.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	Game game;
	game.mainMenu();
	//game.gameMenu();
	system("pause");

	return 0;
}