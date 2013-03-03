#ifndef IBILLBOARDITEM_H
#define IBILLBOARDITEM_H

#include<OgreString.h>
#include<OgreBillboard.h>

class IBillboardItem
{
public:
	virtual const Ogre::String &getResID() const = 0;
	virtual void setBillboard(Ogre::Billboard *b) = 0;
	virtual Ogre::Billboard *getBillboard(void) = 0;
};
#endif