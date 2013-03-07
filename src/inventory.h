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
	void removeItem(Item *item, int x, int y, bool toScene = true);
	int getTotalWeight();
	int getNumberOfItems() { return mItems.size(); }
	Item *getItem(int i) { return mItems.at(i); }
private:
	std::vector<Item *> mItems;
	GameEngine *mEngine;
};

#endif // INVENTORY_H
