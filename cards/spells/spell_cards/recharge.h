#ifndef __RECHARGE_H__
#define __RECHARGE_H__
#include "spell.h"
#include "ritual.h"

class Recharge : public Spell {
    public:
        Recharge(int player);
        virtual ~Recharge();
        bool useSpell(Board &brd, Card &target) override;
   
};


#endif
