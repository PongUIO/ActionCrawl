#ifndef PLAYER_H
#define PLAYER_H
#include "creature.h"

class Player : public Creature
{
public:
	Player();
	virtual ~Player();
	
	void tick();
};

#endif // PLAYER_H
