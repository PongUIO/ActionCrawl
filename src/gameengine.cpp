#include "gameengine.h"

GameEngine::GameEngine(Ogre::SceneManager *manager)
{
	mInitialized = false;
	mSceneMgr = manager;
	mMap = NULL;
}

GameEngine::~GameEngine()
{
	delete mPlayer;

}

void GameEngine::init()
{
	
	mPlayer = new Player(this);
	mPlayer->getPosition() = Ogre::Vector3(5*WORLDSCALE,5*WORLDSCALE,0);
	Item *item = new Item();
	item->getPosition() = Ogre::Vector3(5*WORLDSCALE,5*WORLDSCALE,0);
	mItems.push_back(item);
	addBillboardItemToWorld(*mPlayer, "playerNode");
	addBillboardItemToWorld(*item, "itemNode");
	mMap = new GameMap(256, 256, DUNGEON, mSceneMgr, &mTileSetMgr);
	mInitialized = true;
}

void GameEngine::addBillboardItemToWorld(BillboardItem &item, Ogre::String id)
{
	Ogre::SceneNode *node;
	Ogre::BillboardSet *set = mSceneMgr->createBillboardSet();
	set->setDefaultDimensions(WORLDSCALE, WORLDSCALE);
	set->setMaterialName(item.getResID());
	set->setBounds(Ogre::AxisAlignedBox::BOX_INFINITE, 0);
	item.setBillboard(set->createBillboard(0, 0, 0));
	item.getSceneName() = id;
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode(id);
	node->attachObject(set);
	node->setPosition(0, 0, 4);
}



void GameEngine::tick()
{
	mPlayer->tick();
	std::vector<Item *>::iterator itr = mItems.begin();
	for (itr = mItems.begin(); itr != mItems.end(); itr++) {
		(*itr)->tick();
	}
}


void GameEngine::setKeyState(OIS::KeyCode key, bool pressed) 
{
	mPlayer->feedKey(key, pressed);
}

void GameEngine::updateCamera(Ogre::Camera *camera)
{
	Ogre::Vector3 pos = mPlayer->getPosition();
	camera->setPosition(pos + Ogre::Vector3(0, -80, 80));
	camera->lookAt(pos);
	camera->setNearClipDistance(1);
	camera->setFarClipDistance(500);
}

bool GameEngine::checkCollision(int x, int y)
{
	if (mMap == NULL) {
		return false;
	}
	return mMap->checkCollision(x, y);
}