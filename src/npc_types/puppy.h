#ifndef PUPPY_H
#define PUPPY_H

#include "../npc.h"

class Puppy: public NPC
{

	public:
		Puppy(GameEngine* engine);
		virtual ~Puppy();
		void tick();
};

#endif // PUPPY_H
