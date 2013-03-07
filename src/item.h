#ifndef ITEM_H
#define ITEM_H
class Item;
#include "gamedefines.h"

#include<OgreString.h>
#include<OgreVector3.h>
#include<OgreBillboard.h>
#include<algorithm>

#include "billboarditem.h"
#include "positioneditem.h"
#include "gameengine.h"

class Item : public BillboardItem, public PositionedItem
{
public:
	Item(GameEngine *engine);
	virtual ~Item();
	void tick();
	int getWeight() { return mWeight; }
	bool getInInventory() { return mInInventory; }
	void setInInventory(bool v);
	
protected:
	bool mInInventory;
	ItemType mItemType;
	int mWeight;
	GameEngine *mEngine;
};

#endif // ITEM_H
