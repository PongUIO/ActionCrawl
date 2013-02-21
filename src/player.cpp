#include <OISKeyboard.h>
#include "player.h"

Player::Player() : Creature()
{
	mHealth = 10;
	mMaxHealth = 10;
	mResID = "player";
	mInputFlag.reset();
}

Player::~Player()
{

}

void Player::tick()
{
	Creature::tick();
	
	Ogre::Vector3 move = Ogre::Vector3();
	move.x = move.y = move.z = 0;
	if(mInputFlag[IfLeft]) move.x += 0.5;
	if(mInputFlag[IfRight]) move.x -= 0.5;
	if(mInputFlag[IfForward]) move.y += 0.5;
	if(mInputFlag[IfBack]) move.y -= 0.5;
	mPosition += move;
	
	mBillboard->setPosition(mPosition);
}

void Player::feedKey(const OIS::KeyCode &key, bool press)
{
	switch(key)
	{
		case OIS::KC_LEFT:		mInputFlag[IfLeft] = press; break;
		case OIS::KC_RIGHT:		mInputFlag[IfRight] = press; break;
		case OIS::KC_UP:		mInputFlag[IfForward] = press; break;
		case OIS::KC_DOWN:		mInputFlag[IfBack] = press; break;
		
		default: ;
	}
}
