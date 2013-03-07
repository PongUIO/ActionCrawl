#include "inventory.h"
#include "item.h"
#include "gameengine.h"


Inventory::Inventory(GameEngine *engine)
{
	mEngine = engine;
}

Inventory::~Inventory()
{

}

void Inventory::addItem(Item* item)
{
	mItems.push_back(item);
	mEngine->getSceneMgr()->destroySceneNode(item->getSceneName());
}


int Inventory::getTotalWeight()
{
	int ret = 0;
	std::vector<Item *>::iterator itr;
	for (itr = mItems.begin(); itr != mItems.end(); itr++) {
		ret += (*itr)->getWeight();
	}
	return ret;
}
