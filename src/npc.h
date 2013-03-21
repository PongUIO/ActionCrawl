#ifndef NPC_H
#define NPC_H
#include "creature.h"

class NPC: public Creature
{
	
	public:
		NPC(GameEngine* engine);
		virtual ~NPC();
		
		virtual void tick();
		
	protected:
		const NPC_TYPE mType;
		
};

#endif // NPC_H
