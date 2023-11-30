#ifndef __DARKRITUAL_H__
#define __DARKRITUAL_H__
#include "ritual.h"

class DarkRitual : public Ritual {
    public:
        DarkRitual(string name, string desc, int cost, int player, int actCost, int charges);
        ~DarkRitual();
};


#endif
