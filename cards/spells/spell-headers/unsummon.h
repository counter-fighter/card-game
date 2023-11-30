#ifndef __UNSUMMON_H__
#define __UNSUMMON_H__
#include "spell.h"

class Unsummon : public Spell {
    public:
        Unsummon(string name, string desc, int cost, int player);
        virtual ~Unsummon();

        bool useSpell(Minion* target) const;
   
};


#endif