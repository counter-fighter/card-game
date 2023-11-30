#ifndef __HASTE_H__
#define __HASTE_H__
#include "enchantment.h"

class Haste : public Enchantment {    
    public:
        Haste(string name, string desc, int cost, int player);
        ~Haste();
        void apply(Minion *minion);

};

#endif
