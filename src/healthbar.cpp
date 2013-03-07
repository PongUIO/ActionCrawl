#include <OgreSceneManager.h>

#include "healthbar.h"

HealthBar::HealthBar(Ogre::SceneManager &mgr, Ogre::SceneNode *parentNode)
{
	mBar = mgr.createManualObject();
	mNode = mgr.createSceneNode();
	mNode->attachObject(mBar);
	
	parentNode->addChild(mNode);
	
	mBar->setDynamic(true);
	
	mBar->begin("Simple");
	mBar->end();
	mBar->begin("Simple");
	mBar->end();
}

void HealthBar::updateGeometry()
{
	mBar->beginUpdate(0);
	mBar->colour(Ogre::ColourValue(1,0,0));
	mBar->position(Ogre::Vector3(0,		0,0));
	mBar->position(Ogre::Vector3(0,		mHeight,0));
	mBar->position(Ogre::Vector3(mWidth,	mHeight,0));
	mBar->position(Ogre::Vector3(mWidth,	0,0));
	mBar->end();
	
	mBar->beginUpdate(1);
	mBar->colour(Ogre::ColourValue(0,1,0));
	mBar->position(Ogre::Vector3(0,		0,0));
	mBar->position(Ogre::Vector3(0,		mHeight,0));
	mBar->position(Ogre::Vector3(mWidth*0.5,	mHeight,0));
	mBar->position(Ogre::Vector3(mWidth*0.5,	0,0));
	mBar->end();
}
