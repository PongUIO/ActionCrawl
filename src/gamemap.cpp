#include "gamemap.h"
#include<OgreString.h>
#include<OgreStringConverter.h>
#include<OgreManualObject.h>
#include<boost/random.hpp>
#include<stdlib.h>

GameMap::GameMap(int x, int y, Biome biome, Ogre::SceneManager *manager, TileSetManager *mgr)
{
	mRng.seed();
	mTileSetMgr = mgr;
	mMgr = manager;
	mMObject = mMgr->createManualObject();
	Ogre::SceneNode * node = mMgr->createSceneNode();
	node->attachObject(mMObject);
	node->setPosition(0,0,0);
	mMgr->getRootSceneNode()->addChild(node);
	mXSize = x;
	mYSize = y;
	mMap = new MapTile**[mXSize];
	for (int i = 0; i < mXSize; i++) {
		mMap[i] = new MapTile*[mYSize];
		for (int j = 0; j < mYSize; j++) {
			mMap[i][j] = new MapTile(mTileSetMgr);
		}
	}
	struct MapInfo mapInfo;
	mapInfo.factor1 = 1000;
	mapInfo.factor2 = 200;
	mapInfo.factor3 = 50;
	mapInfo.factor4 = 4;
	mapInfo.corrode = 1;
	mapInfo.torchChance = 1;
	mapInfo.size = 9;
	generateMap(biome, mapInfo);
	updateManualObject();
	//updateTorches();
}

void GameMap::updateTorches()
{
	int c = 0;
	for (int i = 1; i < mXSize-1; i++) {
		for (int j = 1; j < mYSize-1; j++) {
			for (int k = 0; k < 4; k++) {
				if (mMap[i][j]->getTorch(k+1)) {
					char buf[100];
					std::snprintf(buf, sizeof(buf), "light%d", c);
					Ogre::Light *light = mMgr->createLight(buf);
					mLights.push_back(light);
					light->setPosition(getRelX(i, (TileSide)(k+1))*TILESIZE, getRelY(j, (TileSide)(k+1))*TILESIZE, 5);
					c++;
				}
			}
		}
	}
}


void GameMap::generateMap(Biome biome, struct MapInfo m)
{
	if (biome == EMPTY) {
		for (int i = 1; i < mXSize-1; i++) {
			for (int j = 1; j < mYSize-1; j++) {
				mMap[i][j]->setDestroyed(true);
			}
		}
	} else if (biome == DUNGEON) {
		for (int r = 0; r < m.factor1; r++) {
			int xs = mRng() % m.size;
			int ys = mRng() % m.size;
			int x = (mRng() % (mXSize-2-xs)) + 1;
			int y = (mRng() % (mYSize-2-ys)) + 1;
			for (int i = x; i < x + xs; i++) {
				for (int j = y; j < y + ys; j++) {
					
					mMap[i][j]->setDestroyed(true);
				}
			}
		}
		for (int i = 0; i < 1000; i++) {
			int xs = mRng() % 10;
			int ys = mRng() % 10;
			int x = (mRng() % (mXSize-2-xs)) + 1;
			int y = (mRng() % (mYSize-2-ys)) + 1;
			
			generateTunnel(x, y, x+xs, y+ys, 1, 10);
		}
		for (int i = 1; i < mXSize-1; i++) {
			for (int j = 1; j < mYSize-1; j++) {
				if ((int)mRng()%100 < m.factor4) {
					mMap[i][j]->setDestroyed(!mMap[i][j]->getDestroyed());
				}
			}
		}
		for (int i = 1; i < mXSize-1; i++) {
			for (int j = 1; j < mYSize-1; j++) {
				if (mMap[i][j]->getDestroyed() || (analyzeDestroyed(i, j, 1) >= m.corrode && (int)mRng()%100 < m.factor3)) {
					mMap[i][j]->setStoreState(true);
				}
			}
		}
		setAllStoredState();
	}
	if (m.torchChance > 0) {
		for (int i = 1; i < mXSize-1; i++) {
			for (int j = 1; j < mYSize-1; j++) {
				int res = analyzeDestroyed(i,j,1);
				if (res < 4 && mMap[i][j]->getDestroyed() && (int)mRng()%100 < m.torchChance) {
					int rnd = mRng() % (res+1);
					int s;
					for (s = 1; s < 5; s++) {
						if (rnd == 0) {
							break;
						}
						rnd -= getBoundedDestroyed(i, j, (TileSide)s, true);
					}
					mMap[getRelX(i,(TileSide)s)][getRelY(j,(TileSide)s)]->setTorch(flipDirection((TileSide)s), true);
					
				}
			}
		}
	}
}
TileSide GameMap::flipDirection(TileSide side)
{
	if (side == LEFT) {
		return RIGHT;
	} else if (side == RIGHT) {
		return LEFT;
	}
	if (side == UP) {
		return DOWN;
	} else if (side == DOWN) {
		return UP;
	}
	return TOP;
}

void GameMap::setAllStoredState() {
	for (int i = 0; i < mXSize; i++) {
		for (int j = 0; j < mYSize; j++) {
			mMap[i][j]->setDestroyedToStoreState();
		}
	}
}

bool GameMap::getBoundedDestroyed(int x, int y, TileSide side, bool existsCheck)
{
	x = getRelX(x, side);
	y = getRelY(y, side);
	if (x < 0 || x >= mXSize || y < 0 || y >+ mYSize) {
		return !existsCheck;
	}
	return mMap[x][y]->getDestroyed();
}

int GameMap::analyzeDestroyed(int x, int y, int r) {
	int ret = 0;
	for (int i = getBoundedX(x-r, 0); i <= getBoundedX(x+r,0); i++) {
		for (int j = getBoundedX(y-r, 0); j <= getBoundedY(y+r, 0); j++) {
			if ((i == x && j == y) || (std::abs(i-x) + std::abs(j-y)) > r) {
				continue;
			}
			ret += mMap[i][j]->getDestroyed();
		}
	}
	return ret;
}


void GameMap::generateTunnel(int xf, int yf, int xt, int yt, int maxJitter, int jitterChance) 
{
	int xMin = std::min(xf, xt);
	int xMax = std::max(xf, xt);
	int yMin = std::min(yf, yt);
	int yMax = std::max(yf, yt);
	int xOff = (mRng() % (1+2*maxJitter))-maxJitter, yOff = (mRng() % (1+2*maxJitter))-maxJitter;
	Ogre::Vector2 carry = Ogre::Vector2(0,0);
	Ogre::Vector2 prev = carry;
	mMap[xMin][yMin]->setDestroyed(true);
	while (xMin+carry.x < xMax || yMin+carry.y < yMax) {
		if (jitterChance && (int)mRng()%100 < jitterChance) {
			mMap[getBoundedX(xMin+(int)carry.x+xOff, 1)]
			[getBoundedY(yMin+(int)prev.y+yOff, 1)]->setDestroyed(true);
			int fac = 1-2*(mRng()%2);
			if ((int)mRng()%100 < 50) {
				xOff = std::min(maxJitter, std::max(-maxJitter, xOff+fac));
			} else {
				yOff = std::min(maxJitter, std::max(-maxJitter, yOff+fac));
			}
		}
		Ogre::Vector2 vec = Ogre::Vector2(xMax - xMin, yMax - yMin);
		vec.normalise();
		prev = carry;
		carry += vec;
		if ((int)prev.x != (int)carry.x) {
			mMap[getBoundedX(xMin+(int)carry.x+xOff, 1)]
			[getBoundedY(yMin+(int)prev.y+yOff, 1)]->setDestroyed(true);
		}
		if ((int)prev.y != (int)carry.y) {
			mMap[getBoundedX(xMin+(int)prev.x+xOff, 1)]
			[getBoundedY(yMin+(int)carry.y+yOff, 1)]->setDestroyed(true);
		}
	}
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
		x -= 1;
		if (x < 0 || x >= mXSize || !mMap[x][y]->getDestroyed()) {
			return;
		}
		mMObject->position(xt, yt, 0);
		mMObject->position(xt, yt, TILESIZE);
		mMObject->position(xt, yt+TILESIZE, TILESIZE);
		mMObject->position(xt, yt+TILESIZE, 0);
	} else if (side == DOWN) {
		y -= 1;
		if (y < 0 || y >= mYSize || !mMap[x][y]->getDestroyed()) {
			return;
		}
		mMObject->position(xt, yt, 0);
		mMObject->position(xt+TILESIZE, yt, 0);
		mMObject->position(xt+TILESIZE, yt, TILESIZE);
		mMObject->position(xt, yt,TILESIZE);
	} else if (side == RIGHT) {
		x += 1;
		if (x < 0 || x >= mXSize || !mMap[x][y]->getDestroyed()) {
			return;
		}
		mMObject->position(xt+TILESIZE, yt, 0);
		mMObject->position(xt+TILESIZE, yt+TILESIZE, 0);
		mMObject->position(xt+TILESIZE, yt+TILESIZE, TILESIZE);
		mMObject->position(xt+TILESIZE, yt, TILESIZE);
	} else if (side == UP) {
		y += 1;
		if (y < 0 || y >= mYSize || !mMap[x][y]->getDestroyed()) {
			return;
		}
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
	for (int i = 0; i < mXSize; i++) {
		mMap[i] = new MapTile*[mYSize];
		for (int j = 0; j < mYSize; j++) {
			delete mMap[i][j];
		}
		delete mMap[i];
	}
	delete mMap;
}
