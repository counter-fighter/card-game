#ifndef __FIREELEMENTAL_H__
#define __FIREELEMENTAL_H__
#include "minion.h"

class FireElemental : public Minion {
    public:
        FireElemental(string name, string desc, int cost, int atck, int def, int actCount, int actReset, int actCost);
        ~FireElemental();
        void notifyCardMinionEnter();
        void activateAbility();
}


#endif
