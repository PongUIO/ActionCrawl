#ifndef PLAYER_H
#define PLAYER_H
#include <bitset>
#include "creature.h"

class Player : public Creature
{
public:
	Player();
	virtual ~Player();
	
	void tick();
	
	void feedKey(const OIS::KeyCode &key, bool press);
	
private:
	enum InputFlag {
		IfLeft		= 0,
		IfRight		= 1,
		IfForward	= 2,
		IfBack		= 3,
		
		IfMax = 4
	};
	std::bitset<IfMax> mInputFlag;
	
};

#endif // PLAYER_H
