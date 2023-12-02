#ifndef __RITUAL_H__
#define __RITUAL_H__
#include "card.h"
#include "minion.h"

class Ritual : public Card {
    int actCost, charges;
    CardType ct = CardType::Ritual;

    public:
        Ritual(string name, string desc, int cost, int player, int actCost, int charges);
        virtual ~Ritual();
        CardType getCardType() override;
        int getActivationCost();
        int getCharges();
        void setCharges(int n);
};


#endif
