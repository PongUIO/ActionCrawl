#ifndef BILLBOARDITEM_H
#define BILLBOARDITEM_H

#include<OgreString.h>
#include<OgreBillboard.h>

class BillboardItem
{
public:
	const Ogre::String &getResID(void) const { return mResID; }
	const Ogre::String &getSceneName(void) const { return mSceneName; };
	void setBillboard(Ogre::Billboard *b) { mBillboard = b; }
	Ogre::Billboard *getBillboard(void) { return mBillboard; }
	Ogre::String mSceneName, mResID;
	Ogre::Billboard *mBillboard;
};
#endif