#include "Shop.h"
#include <map>
using namespace std;

// Конструктор по подразбиране, с готови цени. (от условието)
Shop::Shop()
{
	items.insert(map<string, int>::value_type("Peasant", PEASANT_PRICE));
	items.insert(map<string, int>::value_type("Footman", FOOTMAN_PRICE));
	items.insert(map<string, int>::value_type("Archer", ARCHER_PRICE));
	items.insert(map<string, int>::value_type("Griffon", GRIFFON_PRICE));
}
// Конструктор по с цени, които сме си въвели, както си искаме.
Shop::Shop(int peasantPrice, int footmanPrice, int archerPrice, int griffonPrice)
{
	items.insert(map<string, int>::value_type("Peasant", peasantPrice));
	items.insert(map<string, int>::value_type("Footman", footmanPrice));
	items.insert(map<string, int>::value_type("Archer", archerPrice));
	items.insert(map<string, int>::value_type("Griffon", griffonPrice));
}

Shop::~Shop()
{
	items.clear();
}

map<string, int> Shop::getItems() const
{
	return this->items;
}
