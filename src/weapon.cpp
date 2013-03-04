#include "weapon.h"

Weapon::Weapon() : Item()
{
	Item::mItemType = WEAPON;
	mWeaponType = SWORD;
}

Weapon::~Weapon()
{

}

