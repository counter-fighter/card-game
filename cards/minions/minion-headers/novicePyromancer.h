#ifndef __NOVICEPYROMANCER_H__
#define __NOVICEPYROMANCER_H__
#include "minion.h"

class NovicePyromancer : public Minion {
    public:
        NovicePyromancer(string name, string desc, int cost, int atck, int def, int actCount, int actReset, int actCost);
        ~NovicePyromancer();
        void activateAbility();
};


#endif
