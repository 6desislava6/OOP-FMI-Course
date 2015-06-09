#include "Battlefield.h"
#include <iostream>
#include <iomanip>

using namespace std;

Battlefield::Battlefield()
{	
	this->coords;

	this->coords.insert(std::make_pair(PPeasantChar, playerPeasantCoords));
	this->coords.insert(std::make_pair(PFootmanChar, playerFootmanCoords));
	this->coords.insert(std::make_pair(PArcherChar, playerArcherCoords));
	this->coords.insert(std::make_pair(PGriffonChar, playerGriffonCoords));

	this->coords.insert(std::make_pair(EPeasantChar, playerPeasantCoords));
	this->coords.insert(std::make_pair(EFootmanChar, enemyFootmanCoords));
	this->coords.insert(std::make_pair(EArcherChar, enemyArcherCoords));
	this->coords.insert(std::make_pair(EGriffonChar, enemyGriffonCoords));



	//fill the matrix with symbols
	for (int i = 0; i < MATRIX_X; i++)
	{
		for (int j = 0; j < MATRIX_Y; j++)
		{
			battlefield[i][j] = BATTLEFIELD_SPACE;
		}
	}

	this->playerPeasantCoords[0] = 0;
	this->playerPeasantCoords[1] = 0;
	battlefield[0][0] = PPeasantChar;

	this->playerFootmanCoords[0] = 0;
	this->playerFootmanCoords[1] = 1;
	battlefield[0][1] = PFootmanChar;

	this->playerArcherCoords[0] = 0;
	this->playerArcherCoords[1] = 2;
	battlefield[0][2] = PArcherChar;

	this->playerGriffonCoords[0] = 0;
	this->playerGriffonCoords[1] = 3;
	battlefield[0][3] = PGriffonChar;


	this->enemyPeasantCoords[0] = MATRIX_X - 1;
	this->enemyPeasantCoords[1] = MATRIX_X - 4;
	battlefield[MATRIX_X - 1][MATRIX_X - 4] = EPeasantChar;

	this->enemyFootmanCoords[0] = MATRIX_X - 1;
	this->enemyFootmanCoords[1] = MATRIX_X - 3;
	battlefield[MATRIX_X - 1][MATRIX_X - 3] = EFootmanChar;

	this->enemyArcherCoords[0] = MATRIX_X - 1;
	this->enemyArcherCoords[1] = MATRIX_X - 2;
	battlefield[MATRIX_X - 1][MATRIX_X - 2] = EArcherChar;

	this->enemyGriffonCoords[0] = MATRIX_X - 1;
	this->enemyGriffonCoords[1] = MATRIX_X - 1;
	battlefield[MATRIX_X - 1][MATRIX_X - 1] = EGriffonChar;
	
}

Battlefield::~Battlefield()
{
	//delete[] battlefield;
	/*delete[] PPeasantChar;
	delete[] PFootmanChar;
	delete[] PArcherChar;
	delete[] PGriffonChar;
	delete[] EPeasantChar;
	delete[] EFootmanChar;
	delete[] EArcherChar;
	delete[] EGriffonChar;*/

	delete[] this->playerPeasantCoords;
	delete[] this->playerFootmanCoords;
	delete[] this->playerArcherCoords;
	delete[] this->playerGriffonCoords;

	delete[] this->enemyPeasantCoords;
	delete[] this->enemyFootmanCoords;
	delete[] this->enemyArcherCoords;
	delete[] this->enemyGriffonCoords;
		
}

int* Battlefield::getPlayerPeasantCoords() const
{
	return this->playerPeasantCoords;
}


int* Battlefield::getPlayerFootmanCoords() const
{
	return this->playerFootmanCoords;
}


int* Battlefield::getPlayerArcherCoords() const
{
	return this->playerArcherCoords;
}


int* Battlefield::getPlayerGriffonCoords() const
{
	return this->playerGriffonCoords;
}


int* Battlefield::getEnemyPeasantCoords() const
{
	return this->enemyPeasantCoords;
}


int* Battlefield::getEnemyFootmanCoords() const
{
	return this->enemyFootmanCoords;
}


int* Battlefield::getEnemyArcherCoords() const
{
	return this->enemyArcherCoords;
}


int* Battlefield::getEnemyGriffonCoords() const
{
	return this->enemyGriffonCoords;
}


void Battlefield::setPlayerPeasantCoords(int x, int y)
{
	int peasant_x = this->playerPeasantCoords[0];
	int peasant_y = this->playerPeasantCoords[1];
	battlefield[peasant_x][peasant_y] = BATTLEFIELD_SPACE;

	this->playerPeasantCoords[0] = x;
	this->playerPeasantCoords[1] = y;
	battlefield[x][y] = PPeasantChar;
}


void Battlefield::setPlayerFootmanCoords(int x, int y)
{
	int footman_x = this->playerFootmanCoords[0];
	int footman_y = this->playerFootmanCoords[1];
	battlefield[footman_x][footman_y] = BATTLEFIELD_SPACE;

	this->playerFootmanCoords[0] = x;
	this->playerFootmanCoords[1] = y;
	battlefield[x][y] = PFootmanChar;
}


void Battlefield::setPlayerArcherCoords(int x, int y)
{
	int archer_x = this->playerArcherCoords[0];
	int archer_y = this->playerArcherCoords[1];
	battlefield[archer_x][archer_y] = BATTLEFIELD_SPACE;

	this->playerArcherCoords[0] = x;
	this->playerArcherCoords[1] = y;
	battlefield[x][y] = PArcherChar;
}


void Battlefield::setPlayerGriffonCoords(int x, int y)
{
	int griffon_x = this->playerGriffonCoords[0];
	int griffon_y = this->playerGriffonCoords[1];
	battlefield[griffon_x][griffon_y] = BATTLEFIELD_SPACE;

	this->playerGriffonCoords[0] = x;
	this->playerGriffonCoords[1] = y;
	battlefield[x][y] = PGriffonChar;
}


void Battlefield::setEnemyPeasantCoords(int x, int y)
{
	int peasant_x = this->enemyPeasantCoords[0];
	int peasant_y = this->enemyPeasantCoords[1];
	battlefield[peasant_x][peasant_y] = BATTLEFIELD_SPACE;

	this->enemyPeasantCoords[0] = x;
	this->enemyPeasantCoords[1] = y;
	battlefield[x][y] = EPeasantChar;
}


void Battlefield::setEnemyFootmanCoords(int x, int y)
{
	int footman_x = this->enemyFootmanCoords[0];
	int footman_y = this->enemyFootmanCoords[1];
	battlefield[footman_x][footman_y] = BATTLEFIELD_SPACE;

	this->enemyFootmanCoords[0] = x;
	this->enemyFootmanCoords[1] = y;
	battlefield[x][y] = EFootmanChar;
}


void Battlefield::setEnemyArcherCoords(int x, int y)
{
	int archer_x = this->enemyArcherCoords[0];
	int archer_y = this->enemyArcherCoords[1];
	battlefield[archer_x][archer_y] = BATTLEFIELD_SPACE;

	this->enemyArcherCoords[0] = x;
	this->enemyArcherCoords[1] = y;
	battlefield[x][y] = EArcherChar;
}


void Battlefield::setEnemyGriffonCoords(int x, int y)
{
	int griffon_x = this->enemyGriffonCoords[0];
	int griffon_y = this->enemyGriffonCoords[1];
	battlefield[griffon_x][griffon_y] = BATTLEFIELD_SPACE;

	this->enemyGriffonCoords[0] = x;
	this->enemyGriffonCoords[1] = y;
	battlefield[x][y] = EGriffonChar;
}


void Battlefield::printBattlefield()
{
	for (int i = 0; i < MATRIX_X; ++i)
	{
		for (int j = 0; j < MATRIX_Y; ++j)
		{
			cout << setw(2) << battlefield[i][j];
		}
		cout << endl;
	}
}

char Battlefield::getBattlefield(int x, int y)
{
	return this->battlefield[x][y];
}

void Battlefield::setCreatureCoords(int x, int y, char creature)
{
	int*	 creature_coords = this->coords[creature];
	int creature_x = creature_coords[0];
	int creature_y = creature_coords[1];
	battlefield[creature_x][creature_y] = BATTLEFIELD_SPACE;

	this->coords[creature][0] = x;
	this->coords[creature][1] = y;
	battlefield[x][y] = creature;
}