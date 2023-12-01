#ifndef __BLIZZARD_H__
#define __BLIZZARD_H__
#include "spell.h"

class Blizzard : public Spell {
    public:
        Blizzard(int player);
        virtual ~Blizzard();   
        bool useSpell(Board &brd, Card &target) override;
};


#endif
