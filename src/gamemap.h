#ifndef GAMEMAP_H
#define GAMEMAP_H
#include<OgreSceneManager.h>
#include<OgreEntity.h>
#include<OgreManualObject.h>
#include "maptile.h"
#include "gamedefines.h"
#include "tilesetmanager.h"

struct MapInfo {
	int factor1, factor2, factor3, factor4, size, corrode, torchChance;
};

class GameMap
{
public:
	GameMap(int, int, Biome, Ogre::SceneManager*, TileSetManager*);
	virtual ~GameMap();
	bool checkCollision(int, int);
protected:
	MapTile ***mMap;
	int mXSize, mYSize;
	Ogre::SceneManager *mMgr;
	Ogre::ManualObject *mMObject;
	TileSetManager *mTileSetMgr;
	boost::rand48 mRng;
	std::vector<Ogre::Light *> mLights;
	
	int getRelX(int x, TileSide side) { return x - (side == LEFT) + (side == RIGHT); }
	int getRelY(int y, TileSide side) { return y - (side == DOWN) + (side == UP); }
	void drawSurface(TileSide, int, int, bool, uint32_t *);
	int analyzeDestroyed(int x, int y, int r);
	void setAllStoredState();
	void updateManualObject(void);
	void updateTorches();
	bool getBoundedDestroyed(int x, int y, TileSide side = TOP, bool existsCheck = false);
	TileSide flipDirection(TileSide side);
	
	int getBoundedX(int v, int b) {return std::min(mXSize-b, std::max(b, v));};
	int getBoundedY(int v, int b) {return std::min(mYSize-b, std::max(b, v));};
	
	void generateMap(Biome, struct MapInfo);
	void generateTunnel(int xf, int yf, int xt, int yt, int maxJitter, int jitterChance);
};

#endif // GAMEMAP_H
