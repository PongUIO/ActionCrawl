#include "item.h"

Item::Item()
{
	mInInventory = false;
	mResID = "erroritem";
	mPosition.x = mPosition.y = mPosition.z = 0;
	mItemType = NONE;
	mInInventory = false;
	mSceneName = "None";
	mBillboard = NULL;
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

