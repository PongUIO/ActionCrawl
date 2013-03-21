#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class Creature;class GameEngine;
class Player;
#include<OgreSceneManager.h>
#include<OgreBillboardSet.h>
#include<OISKeyboard.h>
#include<OgreMovableObject.h>
#include<OgreTextAreaOverlayElement.h>
#include<OgreFontManager.h>
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
	void addBillboardItemToWorld(BillboardItem &item, Ogre::String id);
protected:
	Gorilla::Screen *mScreen;
	Gorilla::Layer *mLayer;
	Gorilla::Rectangle *mBackgroundRect, *mHealthBarRect;
	Ogre::SceneManager *mSceneMgr; 
	Ogre::Overlay *mInventoryOverlay;
	Ogre::OverlayManager *mOverlayMgr;
	std::vector<Item*> mItems;
	std::vector<Creature*> mCreatures;
	BillboardListType mActiveList;
	
	GameMap *mMap;
	bool mInitialized;
	Player *mPlayer;
	double mHUDSizeFactor;
	TileSetManager mTileSetMgr;
	void updateHUD();
	void resizeHUD();
	void createBillboardScreen(BillboardListType type);
	void removeBillboardScreen();
};

#endif // GAMEENGINE_H

