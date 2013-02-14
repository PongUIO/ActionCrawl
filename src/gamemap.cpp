#include "gamemap.h"

GameMap::GameMap(int x, int y, Ogre::SceneManager *manager)
{
	mXSize = x;
	mYSize = y;
	mMap = new MapTile*[mXSize];
	for (int i = 0; i < mXSize; i++) {
		mMap[i] = new MapTile[mYSize];
		for (int j = 0; j < mYSize; j++) {
			mMap[i][j] = MapTile();
		}
	}
}

GameMap::~GameMap()
{

}
