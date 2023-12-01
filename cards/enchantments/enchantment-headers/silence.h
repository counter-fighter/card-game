#ifndef __SILENCE_H__
#define __SILENCE_H__
#include "enchantment.h"

class Silence : public Enchantment {    
    public:
        Silence(string name, string desc, int cost, int player);
        ~Silence();
        void apply(Minion *minion);

};

#endif
