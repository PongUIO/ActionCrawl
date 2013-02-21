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
			mMObject->position(i*10, j*10, 0);
			mMObject->position(i*10, j*10+10, 0);
			mMObject->position(i*10+10, j*10+10, 0);
			mMObject->position(i*10+10, j*10, 0);
			mMObject->quad(count-4, count-3, count-2, count-1);
		}
	}
	mMObject->end();
}


GameMap::~GameMap()
{

}
