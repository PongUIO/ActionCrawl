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

void Item::tick()
{
	if (mBillboard != NULL) {
		mBillboard->setPosition(mPosition);
	}
}

