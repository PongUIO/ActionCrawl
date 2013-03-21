#include "npc.h"

NPC::NPC(GameEngine* engine): Creature(engine)
{
	mHealth = 10;
	mMaxHealth = 10;
	mResID = "npcerror";
	engine->addBillboardItemToWorld(self, mResID);
}

NPC::~NPC()
{

}

void NPC::tick()
{
	Creature::tick();
}
