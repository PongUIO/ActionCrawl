#include "npc.h"

NPC::NPC(GameEngine* engine): Creature(engine), mType(PUPPY)
{
	mHealth = 10;
	mMaxHealth = 10;
	mResID = "errornpc";
	mPosition = Ogre::Vector3(10*WORLDSCALE,10*WORLDSCALE,0);
	engine->addBillboardItemToWorld(*this, "npcnode");
	std::cout << "asd: " << mBillboard << std::endl;
}

NPC::~NPC()
{

}

void NPC::tick()
{
	Creature::tick();
}
