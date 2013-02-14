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

void Creature::tick()
{
	
}

void Creature::heal(int amnt)
{
	mHealth += amnt;
	if(mHealth > mMaxHealth)
		mHealth = mMaxHealth;
}

