#ifndef __MAGICFATIGUE_H__
#define __MAGICFATIGUE_H__
#include "enchantment.h"

class MagicFatigue : public Enchantment {    
    public:
        MagicFatigue(string name, string desc, int cost, int player);
        ~MagicFatigue();
        void apply(Minion *minion);

};

#endif
