#ifndef __RITUAL_H__
#define __RITUAL_H__
#include "card.h"
#include "minion.h"

class Ritual : public Card {
    protected :
        int charges, actCost;
        const CardType ct = CardType::Ritual;
        const TargetType tt = TargetType::NoTarget;

    public:
        Ritual(string name, string desc, int cost, int player, int charges, int actCost);
        virtual ~Ritual();
        CardType getCardType() override;
        TargetType getTargetType() override; 
        int getCharges();
        void setCharges(int n);
        int getActionCost();
};


#endif
