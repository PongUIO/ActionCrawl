#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include<OgreSceneManager.h>
#include<OgreBillboardSet.h>
#include "player.h"

class GameEngine
{
	
public:
	GameEngine(Ogre::SceneManager*);
	virtual ~GameEngine();
	Player player;
	void tick();
protected:
	bool init;
	Ogre::SceneManager *mSceneMgr;
};

#endif // GAMEENGINE_H
