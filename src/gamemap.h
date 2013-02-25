#ifndef GAMEMAP_H
#define GAMEMAP_H
#include<OgreSceneManager.h>
#include<OgreEntity.h>
#include<OgreManualObject.h>
#include "maptile.h"
#include "gamedefines.h"
#include "tilesetmanager.h"

class GameMap
{
public:
	GameMap(int, int, Biome, Ogre::SceneManager*, TileSetManager*);
	void updateManualObject(void);
	virtual ~GameMap();
	bool checkCollision(int, int);
protected:
	MapTile ***mMap;
	int mXSize, mYSize;
	Ogre::ManualObject *mMObject;
	TileSetManager *mTileSetMgr;
	void generateMap(Biome);
	void drawSurface(TileSide, int, int, bool, uint32_t *);
};

#endif // GAMEMAP_H
