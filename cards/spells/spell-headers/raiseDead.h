#ifndef __RAISEDEAD_H__
#define __RAISEDEAD_H__
#include "spell.h"

class RaiseDead : public Spell {
    public:
        RaiseDead(string name, string desc, int cost, int player);
        virtual ~RaiseDead();

        bool useSpell(Minion* target) const;
   
};


#endif
