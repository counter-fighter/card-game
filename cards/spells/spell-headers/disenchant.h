#ifndef __DISENCHANT_H__
#define __DISENCHANT_H__
#include "spell.h"

class Disenchant : public Spell {
    public:
        Disenchant(int player);
        virtual ~Disenchant();
        bool useSpell(Board &brd, Card &target) override;
};


#endif
