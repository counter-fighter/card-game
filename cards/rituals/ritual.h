#ifndef __RITUAL_H__
#define __RITUAL_H__
#include "card.h"
#include "minion.h"

class Ritual : public Card {
    int actCost, charges;
    const CardType ct = CardType::Ritual;
    const TargetType tt = TargetType::NoTarget;

    public:
        Ritual(string name, string desc, int cost, int player, int actCost, int charges);
        virtual ~Ritual();
        CardType getCardType() override;
        TargetType getTargetType() override; 
        int getCharges();
        void setCharges(int n);
        int getActionCost();
};


#endif
