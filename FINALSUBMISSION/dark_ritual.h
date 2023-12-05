#ifndef __DARKRITUAL_H__
#define __DARKRITUAL_H__
#include "ritual.h"

class DarkRitual : public Ritual {
    public:
        DarkRitual(int player);
        ~DarkRitual();
        void notifyCardTurnStart(Board &brd) override; // At the start of your turn, gain 1 magic
};


#endif
