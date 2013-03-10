#ifndef GAMEENGINE_H
#define GAMEENGINE_H
class GameEngine;
class Player;
#include<OgreSceneManager.h>
#include<OgreBillboardSet.h>
#include<OISKeyboard.h>
#include<OgreMovableObject.h>
#include "gamemap.h"
#include "tilesetmanager.h"
#include "item.h"
#include "billboarditem.h"
#include "../gorilla/Gorilla.h"

class GameEngine
{
	
public:
	GameEngine(Ogre::SceneManager*, Gorilla::Screen *screen);
	virtual ~GameEngine();
	void tick();
	void init();
	void setKeyState(OIS::KeyCode, bool);
	void updateCamera(Ogre::Camera *);
	std::vector<Item *> *getItems() { return &mItems; }
	bool getInit() { return mInitialized; }
	bool checkCollision(int, int);
	Ogre::SceneManager* getSceneMgr() { return mSceneMgr; }
	void addToWorld(Ogre::MovableObject *, Ogre::String);
	void setHUDSizeFactor(double factor);
protected:
	Gorilla::Screen *mScreen;
	Gorilla::Layer *mLayer;
	Gorilla::Rectangle *mBackgroundRect, *mHealthBarRect;
	Ogre::SceneManager *mSceneMgr;
	std::vector<Item*> mItems;
	GameMap *mMap;
	bool mInitialized;
	Player *mPlayer;
	double mHUDSizeFactor;
	TileSetManager mTileSetMgr;
	void addBillboardItemToWorld(BillboardItem &item, Ogre::String id);
	void updateHUD();
	void resizeHUD();
};

#endif // GAMEENGINE_H

