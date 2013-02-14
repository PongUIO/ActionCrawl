#include "maptile.h"

MapTile::MapTile()
{
	mDestroyed = true;
	mNode = NULL;
}

MapTile::~MapTile()
{

}

void MapTile::setNode(Ogre::SceneNode *node )
{
	mNode = node;
}