
#ifndef POSITIONEDITEM_H
#define POSITIONEDITEM_H

#include<OgreVector3.h>

class PositionedItem
{
public:
	Ogre::Vector3& getPosition(void) { return mPosition; }
	Ogre::Vector3 mPosition;
};
#endif