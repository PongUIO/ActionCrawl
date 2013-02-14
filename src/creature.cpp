#include "creature.h"

Creature::Creature()
{
	mHealth = 0;
	mMaxHealth = 0;
	mPosition.x = mPosition.y = mPosition.z = 0;
	mBillboard = NULL;
	mResID = "Invalid";
}

Creature::~Creature()
{

}

int Creature::getHealth(void) 
{
	return mHealth;
}

void Creature::setHealth(int v) 
{
	mHealth = std::min(v, mMaxHealth);
}

void Creature::modHealth(int v) 
{
	mHealth = std::min(mHealth+v, mMaxHealth);
}

int Creature::getMaxHealth(void) 
{
	return mMaxHealth;
}

void Creature::setMaxHealth(int v) 
{
	mMaxHealth = v;
}

void Creature::modMaxHealth(int v) 
{
	mMaxHealth += v;
}

Ogre::Vector3* Creature::getPosition(void)
{
	return &mPosition;
}

void Creature::setPosition(Ogre::Vector3 v)
{
	mPosition = v;
}


void Creature::setBillboard(Ogre::Billboard *board)
{
	mBillboard = board;
}

Ogre::Billboard *Creature::getBillboard(void)
{
	return mBillboard;
}

Ogre::String Creature::getResID() 
{
	return mResID;
}