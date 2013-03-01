#ifndef GAMEMAP_H
#define GAMEMAP_H
#include<OgreSceneManager.h>
#include<OgreEntity.h>
#include<OgreManualObject.h>
#include "maptile.h"
#include "gamedefines.h"
#include "tilesetmanager.h"

struct MapInfo {
	int factor1;
	int factor2;
	int factor3;
	int factor4;
	int size;
};

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
	boost::rand48 mRng;
	void drawSurface(TileSide, int, int, bool, uint32_t *);
	int analyzeDestroyed(int x, int y, int r);
	void setAllStoredState();
	
	int getBoundedX(int v, int b) {return std::min(mXSize-b, std::max(b, v));};
	int getBoundedY(int v, int b) {return std::min(mYSize-b, std::max(b, v));};
	
	void generateMap(Biome, struct MapInfo);
	void generateTunnel(int xf, int yf, int xt, int yt, int maxJitter, int jitterChance);
};

#endif // GAMEMAP_H
