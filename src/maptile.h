#ifndef MAPTILE_H
#define MAPTILE_H
#include <OgreSceneNode.h>

class MapTile
{
	
public:
	MapTile();
	virtual ~MapTile();
	void setNode(Ogre::SceneNode *);
protected:
	bool mDestroyed;
	Ogre::SceneNode *mNode;
};

#endif // MAPTILE_H
