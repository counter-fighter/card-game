#ifndef __UNSUMMON_H__
#define __UNSUMMON_H__
#include "spell.h"

class Unsummon : public Spell {
    public:
        Unsummon(int player);
        virtual ~Unsummon();
        void useSpell(Board &brd, Card &target) override;
   
};


#endif
