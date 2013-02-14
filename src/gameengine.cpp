#include "gameengine.h"

GameEngine::GameEngine(Ogre::SceneManager *manager)
{
	mSceneMgr = manager;
}

GameEngine::~GameEngine()
{

}

void GameEngine::init()
{
	Ogre::SceneNode *node;
	Ogre::BillboardSet *set = mSceneMgr->createBillboardSet();
	set->setDefaultDimensions(10, 10);
	set->setMaterialName(player.getResID());
	player.setBillboard(set->createBillboard(0, 0, 0));
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("playerNode");
	node->attachObject(set);
	node->setPosition(0, 0, 0);
}

void GameEngine::tick()
{
	player.tick();
}


void GameEngine::setKeyState(OIS::KeyCode key, bool pressed) 
{
	
}

void GameEngine::updateCamera(Ogre::Camera *camera)
{
	Ogre::Vector3 pos = player.getPosition();
	camera->setPosition(pos - Ogre::Vector3(0, 80, 80));
	camera->lookAt(pos);
}
