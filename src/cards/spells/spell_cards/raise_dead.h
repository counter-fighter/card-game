#ifndef __RAISEDEAD_H__
#define __RAISEDEAD_H__
#include "spell.h"

class RaiseDead : public Spell {
    public:
        RaiseDead(int player);
        virtual ~RaiseDead();
        void useSpell(Board &brd) override;
   
};


#endif
