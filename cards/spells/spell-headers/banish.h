#ifndef __BANISH_H__
#define __BANISH_H__
#include "spell.h"

class Banish : public Spell {
    public:
        Banish(string name, string desc, int cost, int player);
        virtual ~Banish();

        bool useSpell(Minion* target) const;
        bool useSpell(Ritual* target) const;
   
};


#endif
