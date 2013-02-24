#include "maptile.h"

MapTile::MapTile(TileSetManager *mgr)
{
	mDestroyed = true;
	for (int i = 0; i < 5; i++) {
		mSides[i] = mgr->getRandomActiveMaterial();
	}
}

MapTile::~MapTile()
{

}