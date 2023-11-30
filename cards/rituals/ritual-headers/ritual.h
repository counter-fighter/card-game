#ifndef __RITUAL_H__
#define __RITUAL_H__
#include "card.h"

class Ritual : public Card {
    int actCost, charges;

    public:
        Ritual(string name, string desc, int cost, int player, int actCost, int charges);
        virtual ~Ritual() = 0;
        CardType getCardType();
};


#endif
