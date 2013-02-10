#ifndef CREATURE_H
#define CREATURE_H
#include<algorithm>
#include<string>
#include<OgreVector3.h>
#include<OgreBillboard.h>

class Creature
{
	
public:
	Creature();
	virtual ~Creature();
	int getHealth(void);
	void setHealth(int);
	void modHealth(int);
	int getMaxHealth(void);
	void modMaxHealth(int);
	void setMaxHealth(int);
	
	Ogre::Vector3* getPosition(void);
	void setPosition(Ogre::Vector3);
	
	void setBillboard(Ogre::Billboard*);
	Ogre::Billboard *getBillboard(void);
	
	void tick();
	
protected:
	int mHealth;
	int mMaxHealth;
	Ogre::Vector3 mPosition;
	Ogre::Billboard *mBillboard;
	std::string mResID;
	
};

#endif // CREATURE_H
