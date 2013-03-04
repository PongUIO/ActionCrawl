#ifndef CREATURE_H
#define CREATURE_H
#include<OgreString.h>
#include<OgreVector3.h>
#include<OgreBillboard.h>
#include<algorithm>
#include "billboarditem.h"
#include "positioneditem.h"

class Creature : public BillboardItem, public PositionedItem
{
public:
	Creature();
	virtual ~Creature();
	
	int &getHealth() { return mHealth; }
	void heal(int amnt);
	int &getMaxHealth() { return mMaxHealth; }
	Ogre::Vector3& getPosition(void) { return mPosition; }
	
	virtual void tick();
	
protected:
	int mHealth;
	int mMaxHealth;
	Ogre::Vector3 mPosition;
};

#endif // CREATURE_H
