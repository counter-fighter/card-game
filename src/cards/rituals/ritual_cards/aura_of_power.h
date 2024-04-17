#ifndef __AURAOFPOWER_H__
#define __AURAOFPOWER_H__
#include "ritual.h"

class AuraOfPower : public Ritual {
    public:
        AuraOfPower(int player);
        ~AuraOfPower();
        void notifyCardMinionEnter(Board &brd, Card &target) override;
};


#endif
