
#ifndef IPOSITIONEDITEM_H
#define IPOSITIONEDITEM_H

#include<OgreVector3.h>

class IPositionedItem
{
public:
	virtual Ogre::Vector3& getPosition(void)  = 0;
};
#endif