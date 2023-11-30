#ifndef __APPRENTICESUMMONER_H__
#define __APPERNTICESUMMONER_H__
#include "minion.h"

class ApprenticeSummoner : public Minion {
    public:
        ApprenticeSummoner(string name, string desc, int cost, int atck, int def, int actCount, int actReset, int actCost);
        ~ApprenticeSummoner();
        void activateAbility();
}


#endif
