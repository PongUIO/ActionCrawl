#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <OgreManualObject.h>

namespace Ogre { class SceneManager; }

class HealthBar {
public:
	HealthBar(Ogre::SceneManager &mgr, Ogre::SceneNode *parentNode);
	
	void setDimensions(double w, double h)
	{	mWidth = w; mHeight = h; }
	void updateGeometry();
	
	Ogre::SceneNode *getNode() { return mNode; }
	
private:
	Ogre::ManualObject *mBar;
	Ogre::SceneNode *mNode;
	
	double mWidth, mHeight;
};

#endif
