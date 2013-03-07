#include "item.h"

Item::Item(GameEngine *engine)
{
	mEngine = engine;
	mInInventory = false;
	mResID = "erroritem";
	mPosition.x = mPosition.y = mPosition.z = 0;
	mItemType = NONE;
	mInInventory = false;
	mSceneName = "None";
	mBillboard = NULL;
	mWeight = 1;
}

Item::~Item()
{

}

void Item::setInInventory(bool v)
{
	bool prev = mInInventory;
	mInInventory = v;
	if (prev == v) {
		return;
	}
	if (v) {
		mBillboard->mParentSet->removeBillboard(mBillboard);
	} else {
		mBillboard = mBillboard->mParentSet->createBillboard(mPosition);
	}
}


void Item::tick()
{
	if (!mInInventory) {
		mBillboard->setPosition(mPosition);
	}
}

