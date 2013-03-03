#ifndef ITEM_H
#define ITEM_H

#include "gamedefines.h"

#include<OgreString.h>
#include<OgreVector3.h>
#include<OgreBillboard.h>
#include<algorithm>

#include "ibillboarditem.h"
#include "ipositioneditem.h"

class Item : public IBillboardItem, public IPositionedItem
{
public:
	Item();
	virtual ~Item();
	const Ogre::String &getResID() const { return mResID; }
	Ogre::Vector3& getPosition(void) { return mPosition; }
	void setBillboard(Ogre::Billboard *b) { mBillboard = b; }
	Ogre::Billboard *getBillboard(void) { return mBillboard; }
	
	void tick();
protected:
	
	
	Ogre::Vector3 mPosition;
	Ogre::Billboard *mBillboard;
	Ogre::String mResID;
	bool mInInventory;
	ItemType mItemType;
};

#endif // ITEM_H
