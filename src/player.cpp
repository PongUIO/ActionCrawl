#include "player.h"

Player::Player()
{
	Creature();
	mHealth = 10;
	mMaxHealth = 10;
	mResID = "player";
}

Player::~Player()
{

}

void Player::tick()
{
	mPosition.x += 0.1;
	mBillboard->setPosition(mPosition);
}
