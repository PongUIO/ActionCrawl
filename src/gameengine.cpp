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
	player = new Player(this);
	set->setMaterialName(player->getResID());
	set->setBounds(Ogre::AxisAlignedBox::BOX_INFINITE, 0);
	player->setBillboard(set->createBillboard(0, 0, 0));
	player->getPosition() = Ogre::Vector3(5*WORLDSCALE,5*WORLDSCALE,0);
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("playerNode");
	node->attachObject(set);
	node->setPosition(0, 0, 4);
	mMap = new GameMap(16, 16, mSceneMgr);
	mInitialized = true;
}

void GameEngine::tick()
{
	player->tick();
}


void GameEngine::setKeyState(OIS::KeyCode key, bool pressed) 
{
	player->feedKey(key, pressed);
}

void GameEngine::updateCamera(Ogre::Camera *camera)
{
	Ogre::Vector3 pos = player->getPosition();
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