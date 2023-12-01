#ifndef __BANISH_H__
#define __BANISH_H__
#include "spell.h"

class Banish : public Spell {
    public:
        Banish(int player);
        virtual ~Banish();
        bool useSpell(Board &brd, Card &target) override;
   
};


#endif
