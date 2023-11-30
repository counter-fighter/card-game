#ifndef __RECHARGE_H__
#define __RECHARGE_H__
#include "spell.h"

class Recharge : public Spell {
    public:
        Recharge(string name, string desc, int cost, int player);
        virtual ~Recharge();

        bool useSpell(Ritual* target) const;
   
};


#endif
