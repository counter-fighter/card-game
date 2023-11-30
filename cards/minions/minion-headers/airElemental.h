#ifndef __AIRELEMENTAL_H__
#define __AIRELEMENTAL_H__
#include "minion.h"

class AirElemental : public Minion {
    public:
        AirElemental(string name, string desc, int cost, int atck, int def, int actCount, int actReset, int actCost);
        ~AirElemental();

};


#endif
