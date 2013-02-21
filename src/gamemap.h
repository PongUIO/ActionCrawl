#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "maptile.h"
#include<OgreSceneManager.h>
#include<OgreEntity.h>
#include<OgreManualObject.h>
#include "gamedefines.h"

class GameMap
{
public:
	GameMap(int, int, Ogre::SceneManager*);
	void updateManualObject(void);
	virtual ~GameMap();
	bool checkCollision(int, int);
protected:
	MapTile **mMap;
	int mXSize, mYSize;
	Ogre::ManualObject *mMObject;
};

#endif // GAMEMAP_H
