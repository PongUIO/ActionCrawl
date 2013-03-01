#include "maptile.h"

MapTile::MapTile(TileSetManager *mgr)
{
	mDestroyed = false;
	mStoreState = false;
	for (int i = 0; i < 5; i++) {
		mSides[i] = mgr->getRandomActiveMaterial();
		mTorch[i] = false;
	}
}

MapTile::~MapTile()
{

}