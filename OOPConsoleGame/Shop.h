#ifndef SHOP_H
#define SHOP_H
#include <map>

using namespace std;

class Shop
{
public:
	Shop();
	Shop(int peasantPrice, int footmanPrice, int archerPrice, int griffonPrice);
	~Shop();

	map<string, int> getItems() const;

private:
	static const int PEASANT_PRICE = 30;
	static const int FOOTMAN_PRICE = 30;
	static const int ARCHER_PRICE = 50;
	static const int GRIFFON_PRICE = 150;

	map<string, int> items;
};


#endif