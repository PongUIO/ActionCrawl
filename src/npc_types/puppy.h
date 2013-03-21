#ifndef PUPPY_H
#define PUPPY_H

#include "../npc.h"

class Puppy: public NPC
{

	public:
		Puppy();
		virtual ~Puppy();
		void tick();
};

#endif // PUPPY_H
