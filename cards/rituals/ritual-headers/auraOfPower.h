#ifndef __AURAOFPOWER_H__
#define __AURAOFPOWER_H__
#include "ritual.h"

class AuraOfPower : public Ritual {
    public:
        AuraOfPower(string name, string desc, int cost, int player, int actCost, int charges);
        ~AuraOfPower();
};


#endif
