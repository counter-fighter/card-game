#ifndef __ENRAGE_H__
#define __ENRAGE_H__
#include "enchantment.h"

class Enrage : public Enchantment {    
    public:
        Enrage(string name, string desc, int cost, int player);
        ~Enrage();
        void apply(Minion *minion);

};

#endif
