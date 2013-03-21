#include "puppy.h"

Puppy::Puppy(GameEngine* engine) : NPC(engine)
{
	mType = PUPPY;
}

Puppy::~Puppy()
{

}

void Puppy::tick()
{
	
	NPC::tick();
}

