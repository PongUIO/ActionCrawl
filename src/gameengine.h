#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "player.h"

class GameEngine
{
	
public:
	GameEngine();
	virtual ~GameEngine();
	Player player;
};

#endif // GAMEENGINE_H
