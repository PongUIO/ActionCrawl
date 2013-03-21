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
	item->setInInventory(true);
	mItems.push_back(item);
}


void Inventory::removeItem(Item* item, int x, int y, bool toScene)
{
	std::vector<Item *>::iterator itr;
	for (itr = mItems.begin(); itr != mItems.end(); itr++) {
		if (*itr == item) {
			mItems.erase(itr);
			break;
		}
	}
	item->getPosition() = Ogre::Vector3(x, y, 0);
	item->setInInventory(false);
	mEngine->getItems()->push_back(item);
}

Ogre::String Inventory::getNameForEl(int i)
{
	return mItems.at(i)->getName();
}

Ogre::String Inventory::getResIDForEl(int i)
{
	return mItems.at(i)->getResID();
}

Ogre::String Inventory::getSceneNameForEl(int i)
{
	return mItems.at(i)->getSceneName();
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
