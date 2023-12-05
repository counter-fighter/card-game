#ifndef __BLIZZARD_H__
#define __BLIZZARD_H__
#include "spell.h"

class Blizzard : public Spell {
    public:
        Blizzard(int player);
        virtual ~Blizzard();   
        void useSpell(Board &brd) override; // Deal 2 damage to all minions
};


#endif
