#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "maptile.h"
#include<OgreSceneManager.h>
#include<OgreEntity.h>
#include<OgreManualObject.h>

class GameMap
{
public:
	GameMap(int x, int y, Ogre::SceneManager*);
	void updateManualObject(void);
	virtual ~GameMap();
protected:
	MapTile **mMap;
	int mXSize, mYSize;
	Ogre::ManualObject *mMObject;
};

#endif // GAMEMAP_H
