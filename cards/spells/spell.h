#ifndef __MASTERSUMMONER_H__
#define __MASTERSUMMONER_H__
#include "card.h"

class Spell : public Card {
    CardType ct = CardType::Spell;

    public:
        Spell(string name, string desc, int cost, int player);
        virtual ~Spell();
        virtual bool useSpell(Card &target) const = 0;
        CardType getCardType() override;
};


#endif


