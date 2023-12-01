#ifndef __DARKRITUAL_H__
#define __DARKRITUAL_H__
#include "ritual.h"

class DarkRitual : public Ritual {
    public:
        DarkRitual(int player);
        ~DarkRitual();
        void notifyCardTurnStart(Board &brd) override;
};


#endif
