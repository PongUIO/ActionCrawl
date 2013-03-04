#ifndef WEAPON_H
#define WEAPON_H
#include "gamedefines.h"
#include "item.h"

class Weapon : public Item
{
	
public:
	Weapon();
	virtual ~Weapon();
private:
	WeaponType mWeaponType;
};

#endif // WEAPON_H
