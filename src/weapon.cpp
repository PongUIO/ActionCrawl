#include "weapon.h"

Weapon::Weapon(GameEngine *engine) : Item(engine)
{
	Item::mItemType = WEAPON;
	mWeaponType = SWORD;
}

Weapon::~Weapon()
{

}

