#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include <iostream>
#include <string>
#include <vector>
#include <map>

//matrix size
const int MATRIX_X = 10;
const int MATRIX_Y = 10;

//matrix symbols
const char BATTLEFIELD_SPACE = char(46);

const char PPeasantChar = char(80); //P
const char PFootmanChar = char(70); //F
const char PArcherChar = char(65); //A
const char PGriffonChar = char(71); //G

const char EPeasantChar = char(112); //p
const char EFootmanChar = char(102); //f
const char EArcherChar = char(97); //a
const char EGriffonChar = char(103); //g

class Battlefield
{
private:
	char battlefield[MATRIX_X][MATRIX_Y];


	int* playerPeasantCoords = new int[2];
	int* playerFootmanCoords = new int[2];
	int* playerArcherCoords = new int[2];
	int* playerGriffonCoords = new int[2];

	int* enemyPeasantCoords = new int[2];
	int* enemyFootmanCoords = new int[2];
	int* enemyArcherCoords = new int[2];
	int* enemyGriffonCoords = new int[2];


public:
	std::map<char const, int(*)> coords;

	Battlefield();
	~Battlefield();

	int* getPlayerPeasantCoords() const;
	int* getPlayerFootmanCoords() const;
	int* getPlayerArcherCoords() const;
	int* getPlayerGriffonCoords() const;

	int* getEnemyPeasantCoords() const;
	int* getEnemyFootmanCoords() const;
	int* getEnemyArcherCoords() const;
	int* getEnemyGriffonCoords() const;

	char getBattlefield(int x, int y);

	void setPlayerPeasantCoords(int x, int y);
	void setPlayerFootmanCoords(int x, int y);
	void setPlayerArcherCoords(int x, int y);
	void setPlayerGriffonCoords(int x, int y);

	void setEnemyPeasantCoords(int x, int y);
	void setEnemyFootmanCoords(int x, int y);
	void setEnemyArcherCoords(int x, int y);
	void setEnemyGriffonCoords(int x, int y);

	void printBattlefield();
	void setCreatureCoords(int x, int y, char creature);

	void deleteCreatures(int x, int y);

	

};



#endif