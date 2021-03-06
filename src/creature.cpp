#include "creature.h"

Creature::Creature(GameEngine *engine) : mInventory(engine)
{
	mEngine = engine;
	mHealth = 0;
	mMaxHealth = 0;
	mStrength = 0;
	mPosition.x = mPosition.y = mPosition.z = 0;
	mBillboard = NULL;
	mResID = "Invalid";
	mName = "InvalidCreatureName";
	mSceneName = "None";
	mPickupItem = NULL;
	mTicksToItemPickup = 0;
}

void Creature::pickupItem(Item* item)
{
	mTicksToItemPickup = 10;
	mPickupItem = item;
}

void Creature::cancelPickup()
{
	mTicksToItemPickup = 0;
	mPickupItem = NULL;
}

Creature::~Creature()
{

}

void Creature::tick()
{
	assert(mBillboard != NULL && "Creature::tick(), mBillboard == NULL");
	mBillboard->setPosition(mPosition);
	if (mPickupItem != NULL) {
		mTicksToItemPickup -= 1;
	}
	if (mTicksToItemPickup <= 0 && mPickupItem != NULL) {
		mInventory.addItem(mPickupItem);
		mPickupItem = NULL;
		mTicksToItemPickup = 100;
	}
}

void Creature::heal(int amnt)
{
	mHealth = std::max(std::min(mHealth+amnt, mMaxHealth), 0);
}