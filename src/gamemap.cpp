#include "gamemap.h"
#include<OgreString.h>
#include<OgreStringConverter.h>
#include<OgreManualObject.h>

GameMap::GameMap(int x, int y, Ogre::SceneManager *manager)
{
	mMObject = manager->createManualObject();
	Ogre::SceneNode * node = manager->createSceneNode();
	node->attachObject(mMObject);
	node->setPosition(0,0,0);
	manager->getRootSceneNode()->addChild(node);
	mXSize = x;
	mYSize = y;
	mMap = new MapTile*[mXSize];
	for (int i = 0; i < mXSize; i++) {
		mMap[i] = new MapTile[mYSize];
		for (int j = 0; j < mYSize; j++) {
			mMap[i][j] = MapTile();
		}
	}
	mMap[1][1].setDestroyed(false);
	updateManualObject();
}

void GameMap::updateManualObject(void )
{
	mMObject->clear();
	mMObject->estimateIndexCount(mXSize*mYSize*5*4);
	mMObject->estimateVertexCount(mXSize*mYSize*5*4);
	uint32_t count = 0;
	mMObject->begin("rock");
	for (int i = 0; i < mXSize; i++) {
		for (int j = 0; j < mYSize; j++) {
			count+=4;
			int dest = (1-mMap[i][j].getDestroyed())*10;
			mMObject->position(i*TILESIZE+TILESIZE, j*TILESIZE, dest);
			mMObject->position(i*TILESIZE+TILESIZE, j*TILESIZE+TILESIZE, dest);
			mMObject->position(i*TILESIZE, j*TILESIZE+TILESIZE, dest);
			mMObject->position(i*TILESIZE, j*TILESIZE, dest);
			mMObject->quad(count-4, count-3, count-2, count-1);
		}
	}
	mMObject->end();
}

bool GameMap::checkCollision(int x, int y)
{
	
	return (x < 0) || (x > (mXSize*TILESIZE-1))
	|| (y < 0) || (y > (mYSize*TILESIZE-1))
	|| !mMap[x/TILESIZE][y/TILESIZE].getDestroyed();
}


GameMap::~GameMap()
{

}
