#ifndef INVENTORY_H
#define INVENTORY_H
class Inventory;
class Item;
class GameEngine;
#include<stdlib.h>
#include<algorithm>
#include "billboarditem.h"
#include "billboardcollection.h"

class Inventory : public BillboardCollection
{
public:
	Inventory(GameEngine *);
	~Inventory();
	void addItem(Item *item);
	void removeItem(Item *item, int x, int y, bool toScene = true);
	int getTotalWeight();
	uint getNumElements() { return mItems.size(); }
	Ogre::String getResIDForEl(int i); 
	Ogre::String getNameForEl(int i); 
	Ogre::String getSceneNameForEl(int i);
	Item *getItem(int i) { return mItems.at(i); }
	std::vector<Item *> *getVector() { return &mItems; }
private:
	std::vector<Item *> mItems;
	GameEngine *mEngine;
};

#endif // INVENTORY_H
