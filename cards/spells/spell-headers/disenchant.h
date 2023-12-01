#ifndef __DISENCHANT_H__
#define __DISENCHANT_H__
#include "spell.h"

class Disenchant : public Spell {
    public:
        Disenchant(string name, string desc, int cost, int player);
        virtual ~Disenchant();

        bool useSpell(Minion* target) const;
   
};


#endif
