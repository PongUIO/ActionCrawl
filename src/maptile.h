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
	int getMaterial(int side) { return mSides[side]; }
protected:
	bool mDestroyed;
	int mSides[5];
};

#endif // MAPTILE_H
