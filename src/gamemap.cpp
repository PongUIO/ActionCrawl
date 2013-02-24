#include "gamemap.h"
#include<OgreString.h>
#include<OgreStringConverter.h>
#include<OgreManualObject.h>

GameMap::GameMap(int x, int y, Ogre::SceneManager *manager, TileSetManager *mgr)
{
	mTileSetMgr = mgr;
	mMObject = manager->createManualObject();
	Ogre::SceneNode * node = manager->createSceneNode();
	node->attachObject(mMObject);
	node->setPosition(0,0,0);
	manager->getRootSceneNode()->addChild(node);
	mXSize = x;
	mYSize = y;
	mMap = new MapTile**[mXSize];
	for (int i = 0; i < mXSize; i++) {
		mMap[i] = new MapTile*[mYSize];
		for (int j = 0; j < mYSize; j++) {
			mMap[i][j] = new MapTile(mTileSetMgr);
		}
	}
	mMap[1][1]->setDestroyed(false);
	updateManualObject();
}

void GameMap::updateManualObject(void)
{
	mMObject->clear();
	mMObject->estimateIndexCount(mXSize*mYSize*5*4);
	mMObject->estimateVertexCount(mXSize*mYSize*5*4);
	uint32_t count = 0;
	int mat = mTileSetMgr->getActiveLen();
	for (int m = 0; m < mat; m++) {
		count = 0;
		mMObject->begin(mTileSetMgr->getMaterial(m));
		for (int i = 0; i < mXSize; i++) {
			for (int j = 0; j < mYSize; j++) {
				if (m == mMap[i][j]->getMaterial(0)) {
					drawSurface(TOP, i, j, mMap[i][j]->getDestroyed(), &count);
				}
				if (!mMap[i][j]->getDestroyed()) {
					for (int k = 0; k < 4; k++) {
						if (mMap[i][j]->getMaterial(k+1) == m) {
							drawSurface((TileSide)(k+1), i, j, false, &count);
						}
					}
				}
			}
		}
		mMObject->end();
	}
}


void GameMap::drawSurface(TileSide side, int x, int y, bool dest, uint32_t *count)
{
	if ((side != TOP && dest) || side < TOP || UP < side) {
		return;
	}
	int xt = x*TILESIZE;
	int yt = y*TILESIZE;
	if (side == TOP) {
		int z = (1-mMap[x][y]->getDestroyed())*TILESIZE;
		mMObject->position(xt+TILESIZE, yt, z);
		mMObject->position(xt+TILESIZE, yt+TILESIZE, z);
		mMObject->position(xt, yt+TILESIZE, z);
		mMObject->position(xt, yt, z);
	} else if (side == LEFT) {
		mMObject->position(xt, yt, 0);
		mMObject->position(xt, yt, TILESIZE);
		mMObject->position(xt, yt+TILESIZE, TILESIZE);
		mMObject->position(xt, yt+TILESIZE, 0);
	} else if (side == DOWN) {
		mMObject->position(xt, yt, 0);
		mMObject->position(xt+TILESIZE, yt, 0);
		mMObject->position(xt+TILESIZE, yt, TILESIZE);
		mMObject->position(xt, yt,TILESIZE);
	} else if (side == RIGHT) {
		mMObject->position(xt+TILESIZE, yt, 0);
		mMObject->position(xt+TILESIZE, yt+TILESIZE, 0);
		mMObject->position(xt+TILESIZE, yt+TILESIZE, TILESIZE);
		mMObject->position(xt+TILESIZE, yt, TILESIZE);
	} else if (side == UP) {
		mMObject->position(xt, yt + TILESIZE, 0);
		mMObject->position(xt, yt + TILESIZE,TILESIZE);
		mMObject->position(xt+TILESIZE, yt + TILESIZE, TILESIZE);
		mMObject->position(xt+TILESIZE, yt + TILESIZE, 0);
	} else {
		return;
	}
	*count =*count + 4;
	mMObject->quad(*count-4, *count-3, *count-2, *count-1);
}


bool GameMap::checkCollision(int x, int y)
{
	
	return (x < 0) || (x > (mXSize*TILESIZE-1))
	|| (y < 0) || (y > (mYSize*TILESIZE-1))
	|| !mMap[x/TILESIZE][y/TILESIZE]->getDestroyed();
}


GameMap::~GameMap()
{

}
