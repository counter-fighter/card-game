#ifndef __ENCHANTMENT_H__
#define __ENCHANTMENT_H__
#include "card.h"
#include "minion.h"

class Enchantment : public Card {
    protected:
        CardType ct = CardType::Enchantment;

        Enchantment(string name, string desc, int cost);
        virtual ~Enchantment();

        void setAttack(Minion *target, int n);
        void setDefence(Minion *target, int n);
        void setActReset(Minion *target, int n);
        void setActCost(Minion *target, int n);
    public :
        virtual void attach(Minion *target) = 0;
};



#endif