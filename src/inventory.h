#ifndef INVENTORY_H
#define INVENTORY_H
class Inventory;
class Item;
class GameEngine;
#include<stdlib.h>
#include<algorithm>

class Inventory
{
public:
	Inventory(GameEngine *);
	~Inventory();
	void addItem(Item *item);
	int getTotalWeight();
private:
	std::vector<Item *> mItems;
	GameEngine *mEngine;
};

#endif // INVENTORY_H
