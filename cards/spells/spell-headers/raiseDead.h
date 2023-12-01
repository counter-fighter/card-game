#ifndef __RAISEDEAD_H__
#define __RAISEDEAD_H__
#include "spell.h"

class RaiseDead : public Spell {
    public:
        RaiseDead(int player);
        virtual ~RaiseDead();
        bool useSpell(Board &brd, Card &target) override;
   
};


#endif
