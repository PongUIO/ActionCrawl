#include "gamemap.h"
#include<OgreString.h>
#include <OgreStringConverter.h>

GameMap::GameMap(int x, int y, Ogre::SceneManager *manager)
{
	mXSize = x;
	mYSize = y;
	mMap = new MapTile*[mXSize];
	Ogre::StringConverter convert;
	for (int i = 0; i < mXSize; i++) {
		mMap[i] = new MapTile[mYSize];
		for (int j = 0; j < mYSize; j++) {
			Ogre::String name = convert.toString(i)+"box" + convert.toString(j);
			Ogre::Entity *box = manager->createEntity(name, "terrain/box.mesh");
			Ogre::SceneNode *node = manager->getRootSceneNode()->createChildSceneNode(name);
			node->attachObject(box);
			node->setPosition(i,j,0);
			mMap[i][j] = MapTile();
			mMap[i][j].setNode(node);
		}
	}
}

GameMap::~GameMap()
{

}
