#ifndef CREATURE_H
#define CREATURE_H
#include<OgreString.h>
#include<OgreVector3.h>
#include<OgreBillboard.h>
#include<algorithm>
#include "gameengine.h"
#include "item.h"
#include "billboarditem.h"
#include "positioneditem.h"
#include "inventory.h"

class Creature : public BillboardItem, public PositionedItem
{
public:
	Creature(GameEngine* engine);
	virtual ~Creature();
	
	int getHealth() { return mHealth; }
	void heal(int amnt);
	int &getMaxHealth() { return mMaxHealth; }
	Ogre::Vector3& getPosition(void) { return mPosition; }
	void pickupItem(Item *item);
	void cancelPickup();
	virtual void tick();
	Inventory *getInventory() { return &mInventory; }
	
protected:
	int mHealth;
	int mMaxHealth;
	int mStrength;
	Item *mPickupItem;
	int mTicksToItemPickup;
	Inventory mInventory;
	Ogre::Vector3 mPosition;
	GameEngine *mEngine;
};

#endif // CREATURE_H
