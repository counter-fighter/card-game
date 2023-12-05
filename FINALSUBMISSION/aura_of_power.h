#ifndef __AURAOFPOWER_H__
#define __AURAOFPOWER_H__
#include "ritual.h"

class AuraOfPower : public Ritual {
    public:
        AuraOfPower(int player);
        ~AuraOfPower();
        void notifyCardMinionEnter(Board &brd, Card &target) override; // Whenever a minion enters play under your control, it gains +1/+1
};


#endif
