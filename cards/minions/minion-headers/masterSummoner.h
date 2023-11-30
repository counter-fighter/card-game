#ifndef __MASTERSUMMONER_H__
#define __MASTERSUMMONER_H__
#include "minion.h"

class MasterSummoner : public Minion {
    public:
        MasterSummoner(string name, string desc, int cost, int atck, int def, int actCount, int actReset, int actCost);
        ~MasterSummoner();
        void activateAbility();
}


#endif
