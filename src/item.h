#ifndef ITEM_H
#define ITEM_H

#include "gamedefines.h"

#include<OgreString.h>
#include<OgreVector3.h>
#include<OgreBillboard.h>
#include<algorithm>

#include "billboarditem.h"
#include "positioneditem.h"

class Item : public BillboardItem, public PositionedItem
{
public:
	Item();
	virtual ~Item();
	void tick();
	
protected:
	bool mInInventory;
	ItemType mItemType;
};

#endif // ITEM_H
