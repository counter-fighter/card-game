#ifndef __BANISH_H__
#define __BANISH_H__
#include "spell.h"


class Banish : public Spell {
    public:
        Banish(int player);
        virtual ~Banish();
        void useSpell(Board &brd, Card &target) override; // Destroy target minion or ritual
   
};


#endif
