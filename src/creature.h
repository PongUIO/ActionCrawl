#ifndef CREATURE_H
#define CREATURE_H
#include<OgreString.h>
#include<OgreVector3.h>
#include<OgreBillboard.h>
#include<algorithm>

class Creature
{
public:
	Creature();
	virtual ~Creature();
	
	int &getHealth() { return mHealth; }
	void heal(int amnt);
	int &getMaxHealth() { return mMaxHealth; }
	Ogre::Vector3& getPosition(void) { return mPosition; }
	const std::string &getResID() const { return mResID; }
	
	void setBillboard(Ogre::Billboard *b) { mBillboard = b; }
	Ogre::Billboard *getBillboard(void) { return mBillboard; }
	
	virtual void tick();
	
protected:
	int mHealth;
	int mMaxHealth;
	Ogre::Vector3 mPosition;
	Ogre::Billboard *mBillboard;
	Ogre::String mResID;
};

#endif // CREATURE_H
