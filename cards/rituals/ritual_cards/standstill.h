#ifndef __STANDSTILL_H__
#define __STANDSTILL_H__
#include "ritual.h"

class Standstill : public Ritual {
    public:
        Standstill(int player);
        ~Standstill();
        void notifyCardMinionEnter(Board &brd, Card &target) override;
};


#endif
