#ifndef __DISENCHANT_H__
#define __DISENCHANT_H__
#include "spell.h"

class Disenchant : public Spell {
    public:
        Disenchant(int player);
        virtual ~Disenchant();
        void useSpell(Board &brd, Card &target) override; //Destroy top enchantment on target minion
};


#endif
