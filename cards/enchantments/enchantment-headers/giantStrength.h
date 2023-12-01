#ifndef __GIANTSTRENGTH_H__
#define __GIANTSTRENGTH_H__
#include "enchantment.h"

class GiantStrength : public Enchantment {    
    public:
        GiantStrength(string name, string desc, int cost, int player);
        ~GiantStrength();
        void apply(Minion *minion);

};

#endif
