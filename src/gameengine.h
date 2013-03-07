#ifndef GAMEENGINE_H
#define GAMEENGINE_H
class GameEngine;
class Player;
#include<OgreSceneManager.h>
#include<OgreBillboardSet.h>
#include<OISKeyboard.h>
#include "gamemap.h"
#include "tilesetmanager.h"
#include "item.h"
#include "billboarditem.h"

class GameEngine
{
	
public:
	GameEngine(Ogre::SceneManager*);
	virtual ~GameEngine();
	void tick();
	void init();
	void setKeyState(OIS::KeyCode, bool);
	void updateCamera(Ogre::Camera *);
	std::vector<Item *> *getItems() { return &mItems; }
	bool getInit() { return mInitialized; }
	bool checkCollision(int, int);
	Ogre::SceneManager* getSceneMgr() { return mSceneMgr; }
protected:
	Ogre::SceneManager *mSceneMgr;
	std::vector<Item*> mItems;
	GameMap *mMap;
	bool mInitialized;
	Player *mPlayer;
	TileSetManager mTileSetMgr;
	void addBillboardItemToWorld(BillboardItem &item, Ogre::String id);
};

#endif // GAMEENGINE_H

