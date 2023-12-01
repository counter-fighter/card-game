#ifndef __ENCHANTMENT_H__
#define __ENCHANTMENT_H__
#include "card.h"

class Enchantment : public Card {
    // We need to decide on smart pointer type to define it here
    CardType ct = CardType::Enchantment;
    
    public:
        Enchantment(string name, string desc, int cost, int player);
        virtual ~Enchantment() = 0;
        virtual void apply(Minion *minion) = 0;
        CardType getCardType();
};

#endif
