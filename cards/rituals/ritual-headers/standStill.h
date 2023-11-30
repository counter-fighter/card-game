#ifndef __STANDSTILL_H__
#define __STANDSTILL_H__
#include "ritual.h"

class StandStill : public Ritual {
    public:
        StandStill(string name, string desc, int cost, int player, int actCost, int charges);
        ~StandStill();
};


#endif
