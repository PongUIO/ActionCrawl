#ifndef MAPTILE_H
#define MAPTILE_H
#include <OgreSceneNode.h>

class MapTile
{
	
public:
	MapTile();
	virtual ~MapTile();
protected:
	bool mDestroyed;
};

#endif // MAPTILE_H
