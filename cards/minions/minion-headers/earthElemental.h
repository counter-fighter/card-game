#ifndef __EARTHELEMENTAL_H__
#define __EARTHELEMENTAL_H__
#include "minion.h"

class EarthElemental : public Minion {
    public:
        EarthElemental(string name, string desc, int cost, int atck, int def, int actCount, int actReset, int actCost);
        ~EarthElemental();
}


#endif
