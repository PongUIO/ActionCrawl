#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include<OgreSceneManager.h>
#include<OgreBillboardSet.h>
#include<OISKeyboard.h>
#include "player.h"
#include "gamemap.h"

class GameEngine
{
	
public:
	GameEngine(Ogre::SceneManager*);
	virtual ~GameEngine();
	Player player;
	void tick();
	void init();
	void setKeyState(OIS::KeyCode, bool);
	void updateCamera(Ogre::Camera *);
protected:
	Ogre::SceneManager *mSceneMgr;
	GameMap *mMap;
};

#endif // GAMEENGINE_H
