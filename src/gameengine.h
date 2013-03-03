#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include<OgreSceneManager.h>
#include<OgreBillboardSet.h>
#include<OISKeyboard.h>
#include "player.h"
#include "gamemap.h"
#include "tilesetmanager.h"
#include "item.h"
#include "ibillboarditem.h"

class GameEngine
{
	
public:
	GameEngine(Ogre::SceneManager*);
	virtual ~GameEngine();
	void tick();
	void init();
	void setKeyState(OIS::KeyCode, bool);
	void updateCamera(Ogre::Camera *);
	bool getInit() { return mInitialized; }
	bool checkCollision(int, int);
protected:
	Ogre::SceneManager *mSceneMgr;
	std::vector<Item*> mItems;
	GameMap *mMap;
	bool mInitialized;
	Player *mPlayer;
	TileSetManager mTileSetMgr;
	void addBillboardItemToWorld(IBillboardItem &item, Ogre::String id);
};

#endif // GAMEENGINE_H

