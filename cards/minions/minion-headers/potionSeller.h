#ifndef __POTIONSELLER_H__
#define __POTIONSELLER_H__
#include "minion.h"

class PotionSeller : public Minion {
    public:
        PotionSeller(string name, string desc, int cost, int atck, int def, int actCount, int actReset, int actCost);
        ~PotionSeller();
        void notifyCardTurnEnd();
        void activateAbility();
}


#endif
