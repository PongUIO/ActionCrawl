#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "maptile.h"
#include<OgreSceneManager.h>
class GameMap
{
	GameMap(int x, int y, Ogre::SceneManager*);
	virtual ~GameMap();
protected:
	MapTile **mMap;
	int mXSize, mYSize;
};

#endif // GAMEMAP_H
