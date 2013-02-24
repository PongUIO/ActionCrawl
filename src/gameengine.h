#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include<OgreSceneManager.h>
#include<OgreBillboardSet.h>
#include<OISKeyboard.h>
#include "player.h"
#include "gamemap.h"
#include "tilesetmanager.h"

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
	GameMap *mMap;
	bool mInitialized;
	Player *mPlayer;
	TileSetManager mTileSetMgr;
	
};

#endif // GAMEENGINE_H

