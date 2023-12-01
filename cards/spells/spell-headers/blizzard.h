#ifndef __BLIZZARD_H__
#define __BLIZZARD_H__
#include "spell.h"

class Blizzard : public Spell {
    public:
        Blizzard(string name, string desc, int cost, int player);
        virtual ~Blizzard();   
};


#endif
