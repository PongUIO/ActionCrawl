#include "gameengine.h"

GameEngine::GameEngine(Ogre::SceneManager *manager)
{
	mSceneMgr = manager; 
	init = 0;
}

GameEngine::~GameEngine()
{

}

void GameEngine::tick()
{
	if (!init) {
		init = 1;
		Ogre::SceneNode *node;
		Ogre::BillboardSet *set = mSceneMgr->createBillboardSet();
		set->setDefaultDimensions(10, 10);
		set->setMaterialName(player.getResID());
		player.setBillboard(set->createBillboard(0, 0, 0));
		node = mSceneMgr->getRootSceneNode()->createChildSceneNode("playerNode");
		node->attachObject(set);
		node->setPosition(0, 0, 0);
	}
	player.tick();
}


void GameEngine::setKeyState(OIS::KeyCode key, bool pressed) 
{
	
}