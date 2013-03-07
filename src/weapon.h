#ifndef WEAPON_H
#define WEAPON_H
#include "gamedefines.h"
#include "gameengine.h"
#include "item.h"

class Weapon : public Item
{
	
public:
	Weapon(GameEngine *engine);
	virtual ~Weapon();
private:
	WeaponType mWeaponType;
};

#endif // WEAPON_H
