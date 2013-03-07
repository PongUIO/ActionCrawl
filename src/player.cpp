#include <OISKeyboard.h>
#include "player.h"
#include "gameengine.h"

Player::Player(GameEngine *engine) : Creature(engine)
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
	if (mInputFlag[IfG]) {
		std::vector<Item *> *items = mEngine->getItems();
		std::vector<Item *>::iterator itr;
		for (itr = items->begin(); itr != items->end(); itr++) {
			Creature::pickupItem((*itr));
			break;
		}
	}
	
	if (mInputFlag[IfH]) {
		if (mInventory.getNumberOfItems() > 0) {
			mInventory.removeItem(mInventory.getItem(0), mPosition.x, mPosition.y);
		}
	}
	
	Ogre::Vector3 move = Ogre::Vector3();
	move.x = move.y = move.z = 0;
	if(mInputFlag[IfLeft]) move.x -= 0.5;
	if(mInputFlag[IfRight]) move.x += 0.5;
	if(mInputFlag[IfForward]) move.y += 0.5;
	if(mInputFlag[IfBack]) move.y -= 0.5;
	if (move.length() > 0.01) {
		Creature::cancelPickup();
	}
	mPosition += move;
	/*if (mEngine->checkCollision(mPosition.x, mPosition.y)) {
		mPosition-=move;
	}*/
	
	if (mBillboard != NULL) {
		mBillboard->setPosition(mPosition);
	}
}

void Player::feedKey(const OIS::KeyCode &key, bool press)
{
	switch(key)
	{
		case OIS::KC_LEFT:		mInputFlag[IfLeft] = press; break;
		case OIS::KC_RIGHT:		mInputFlag[IfRight] = press; break;
		case OIS::KC_UP:		mInputFlag[IfForward] = press; break;
		case OIS::KC_DOWN:		mInputFlag[IfBack] = press; break;
		case OIS::KC_G:			mInputFlag[IfG] = press; break;
		case OIS::KC_H:			mInputFlag[IfH] = press; break;
		
		default: ;
	}
}
