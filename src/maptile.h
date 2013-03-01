#ifndef MAPTILE_H
#define MAPTILE_H
#include<OgreSceneNode.h>
#include "tilesetmanager.h"
#include "gamedefines.h"

class MapTile
{
	
public:
	MapTile(TileSetManager *mgr);
	virtual ~MapTile();
	void setDestroyed(bool v) { mDestroyed = v; }
	bool getDestroyed() { return mDestroyed; }
	void setStoreState(bool v) { mStoreState = v; }
	void setDestroyedToStoreState() { mDestroyed = mStoreState; }
	int getMaterial(int side) { return mSides[side]; }
	bool getTorch(int side) { return mTorch[side]; }
	void setTorch(int side, bool state) { mTorch[side] = state; }
	void setTorch(TileSide side, bool state) { mTorch[(int)side] = state; }
protected:
	bool mDestroyed;
	bool mStoreState;
	int mSides[5];
	bool mTorch[5];
};

#endif // MAPTILE_H
