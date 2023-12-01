#ifndef __STANDSTILL_H__
#define __STANDSTILL_H__
#include "ritual.h"

class StandStill : public Ritual {
    public:
        StandStill(int player);
        ~StandStill();
        void notifyCardMinionEnter(Board &brd, Card &target) override;
};


#endif
