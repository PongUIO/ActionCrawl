#ifndef MAPTILE_H
#define MAPTILE_H
#include <OgreSceneNode.h>

class MapTile
{
	
public:
	MapTile();
	virtual ~MapTile();
	void setDestroyed(bool v) { mDestroyed = v; }
	bool getDestroyed() { return mDestroyed; }
protected:
	bool mDestroyed;
};

#endif // MAPTILE_H
