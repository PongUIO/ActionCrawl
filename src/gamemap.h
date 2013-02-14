#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "maptile.h"
#include<OgreSceneManager.h>
#include<OgreEntity.h>

class GameMap
{
public:
	GameMap(int x, int y, Ogre::SceneManager*);
	virtual ~GameMap();
protected:
	MapTile **mMap;
	int mXSize, mYSize;
};

#endif // GAMEMAP_H
