#include "gameengine.h"

GameEngine::GameEngine(Ogre::SceneManager *manager)
{
	mInitialized = false;
	mSceneMgr = manager;
	mMap = NULL;
}

GameEngine::~GameEngine()
{

}

void GameEngine::init()
{
	Ogre::SceneNode *node;
	Ogre::BillboardSet *set = mSceneMgr->createBillboardSet();
	set->setDefaultDimensions(WORLDSCALE, WORLDSCALE);
	mPlayer = new Player(this);
	set->setMaterialName(mPlayer->getResID());
	set->setBounds(Ogre::AxisAlignedBox::BOX_INFINITE, 0);
	mPlayer->setBillboard(set->createBillboard(0, 0, 0));
	mPlayer->getPosition() = Ogre::Vector3(5*WORLDSCALE,5*WORLDSCALE,0);
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("playerNode");
	node->attachObject(set);
	node->setPosition(0, 0, 4);
	mMap = new GameMap(256, 256, DUNGEON, mSceneMgr, &mTileSetMgr);
	mInitialized = true;
}

void GameEngine::tick()
{
	mPlayer->tick();
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