#ifndef __RECHARGE_H__
#define __RECHARGE_H__
#include "spell.h"
#include "ritual.h"
#include "board.h"

class Recharge : public Spell {
    public:
        Recharge(int player);
        virtual ~Recharge();
        void useSpell(Board &brd) override;
   
};


#endif
