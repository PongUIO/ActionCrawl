#ifndef MAPTILE_H
#define MAPTILE_H
#include<OgreSceneNode.h>
#include "tilesetmanager.h"

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
protected:
	bool mDestroyed;
	bool mStoreState;
	int mSides[5];
};

#endif // MAPTILE_H
